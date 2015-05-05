/*
 * net/dsa/mv88e6131.c - Marvell 88e6095/6095f/6131 switch chip support
 * Copyright (c) 2008-2009 Marvell Semiconductor
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/phy.h>
#include <net/dsa.h>
#include "mv88e6xxx.h"

static char *mv88e6131_probe(struct device *host_dev, int sw_addr)
{
	struct mii_bus *bus = dsa_host_dev_to_mii_bus(host_dev);
	int ret;

	if (bus == NULL)
		return NULL;

	ret = __mv88e6xxx_reg_read(bus, sw_addr, REG_PORT(0), PORT_SWITCH_ID);
	if (ret >= 0) {
		int ret_masked = ret & 0xfff0;

		if (ret_masked == PORT_SWITCH_ID_6085)
			return "Marvell 88E6085";
		if (ret_masked == PORT_SWITCH_ID_6095)
			return "Marvell 88E6095/88E6095F";
		if (ret == PORT_SWITCH_ID_6131_B2)
			return "Marvell 88E6131 (B2)";
		if (ret_masked == PORT_SWITCH_ID_6131)
			return "Marvell 88E6131";
	}

	return NULL;
}

static int mv88e6131_setup_global(struct dsa_switch *ds)
{
	int ret;

	ret = mv88e6xxx_setup_global(ds);
	if (ret)
		return ret;

	/* Enable the PHY polling unit, don't discard packets with
	 * excessive collisions, use a weighted fair queueing scheme
	 * to arbitrate between packet queues, set the maximum frame
	 * size to 1632, and mask all interrupt sources.
	 */
	REG_WRITE(REG_GLOBAL, 0x04, 0x4400);

	/* Set the VLAN ethertype to 0x8100. */
	REG_WRITE(REG_GLOBAL, 0x19, 0x8100);

	/* Disable ARP mirroring, and configure the upstream port as
	 * the port to which ingress and egress monitor frames are to
	 * be sent.
	 */
	REG_WRITE(REG_GLOBAL, 0x1a, (dsa_upstream_port(ds) * 0x1100) | 0x00f0);

	/* Disable cascade port functionality unless this device
	 * is used in a cascade configuration, and set the switch's
	 * DSA device number.
	 */
	if (ds->dst->pd->nr_chips > 1)
		REG_WRITE(REG_GLOBAL, 0x1c, 0xf000 | (ds->index & 0x1f));
	else
		REG_WRITE(REG_GLOBAL, 0x1c, 0xe000 | (ds->index & 0x1f));

	/* Force the priority of IGMP/MLD snoop frames and ARP frames
	 * to the highest setting.
	 */
	REG_WRITE(REG_GLOBAL2, 0x0f, 0x00ff);

	return 0;
}

static int mv88e6131_setup(struct dsa_switch *ds)
{
	struct mv88e6xxx_priv_state *ps = ds_to_priv(ds);
	int i;
	int ret;

	ret = mv88e6xxx_setup_common(ds);
	if (ret < 0)
		return ret;

	mv88e6xxx_ppu_state_init(ds);

	switch (ps->id) {
	case PORT_SWITCH_ID_6085:
		ps->num_ports = 10;
		break;
	case PORT_SWITCH_ID_6095:
		ps->num_ports = 11;
		break;
	case PORT_SWITCH_ID_6131:
	case PORT_SWITCH_ID_6131_B2:
		ps->num_ports = 8;
		break;
	default:
		return -ENODEV;
	}

	ret = mv88e6xxx_switch_reset(ds, false);
	if (ret < 0)
		return ret;

	ret = mv88e6131_setup_global(ds);
	if (ret < 0)
		return ret;

	for (i = 0; i < ps->num_ports; i++) {
		ret = mv88e6xxx_setup_port(ds, i);
		if (ret < 0)
			return ret;
	}

	return 0;
}

static int mv88e6131_port_to_phy_addr(struct dsa_switch *ds, int port)
{
	struct mv88e6xxx_priv_state *ps = ds_to_priv(ds);

	if (port >= 0 && port < ps->num_ports)
		return port;

	return -EINVAL;
}

static int
mv88e6131_phy_read(struct dsa_switch *ds, int port, int regnum)
{
	int addr = mv88e6131_port_to_phy_addr(ds, port);

	if (addr < 0)
		return addr;

	return mv88e6xxx_phy_read_ppu(ds, addr, regnum);
}

static int
mv88e6131_phy_write(struct dsa_switch *ds,
			      int port, int regnum, u16 val)
{
	int addr = mv88e6131_port_to_phy_addr(ds, port);

	if (addr < 0)
		return addr;

	return mv88e6xxx_phy_write_ppu(ds, addr, regnum, val);
}

struct dsa_switch_driver mv88e6131_switch_driver = {
	.tag_protocol		= DSA_TAG_PROTO_DSA,
	.priv_size		= sizeof(struct mv88e6xxx_priv_state),
	.probe			= mv88e6131_probe,
	.setup			= mv88e6131_setup,
	.set_addr		= mv88e6xxx_set_addr_direct,
	.phy_read		= mv88e6131_phy_read,
	.phy_write		= mv88e6131_phy_write,
	.poll_link		= mv88e6xxx_poll_link,
	.get_strings		= mv88e6xxx_get_strings,
	.get_ethtool_stats	= mv88e6xxx_get_ethtool_stats,
	.get_sset_count		= mv88e6xxx_get_sset_count,
};

MODULE_ALIAS("platform:mv88e6085");
MODULE_ALIAS("platform:mv88e6095");
MODULE_ALIAS("platform:mv88e6095f");
MODULE_ALIAS("platform:mv88e6131");
