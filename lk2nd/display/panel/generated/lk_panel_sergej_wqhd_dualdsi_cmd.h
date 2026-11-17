// SPDX-License-Identifier: GPL-2.0-only
/*
 * Lumia 950 XL (cityman) "Sergej" 1440x2560 AMOLED, dual DSI command mode.
 * Values from the cityman kernel device tree
 * (arch/arm64/boot/dts/mmo/panels/dsi-panel-sergej-wqhd-dualdsi-cmd.dtsi),
 * laid out like panel_jdi_qhd_dualdsi_cmd.h, the MSM8994 MTP dual DSI command panel.
 * Each DSI link drives one 720x2560 half; commands are broadcast to both.
 */

#ifndef _PANEL_SERGEJ_WQHD_DUALDSI_CMD_H_
#define _PANEL_SERGEJ_WQHD_DUALDSI_CMD_H_

#include <mipi_dsi.h>
#include <panel_display.h>
#include <panel.h>
#include <string.h>

static struct panel_config sergej_wqhd_dualdsi_cmd_panel_data = {
	"qcom,mdss_dsi_sergej_wqhd_dsi0_cmd", "dsi:0:", "qcom,mdss-dsi-panel",
	10, 1, "DISPLAY_1", 0, 0, 60, 0, 0, 1, 0, 0, 0, 0, 0,
	DUAL_DSI_FLAG | DUAL_PIPE_FLAG | SPLIT_DISPLAY_FLAG, 0, 0,
	"qcom,mdss_dsi_sergej_wqhd_dsi1_cmd"
};

static struct panel_resolution sergej_wqhd_dualdsi_cmd_panel_res = {
	1440, 2560, 76, 32, 16, 0, 4, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static struct color_info sergej_wqhd_dualdsi_cmd_color = {
	24, 0, 0xff, 0, 0, 0
};

/* exit_sleep_mode, then 5 ms */
static char sergej_on_cmd0[] = { 0x11, 0x00, 0x05, 0x80 };
/* level 2 unlock */
static char sergej_on_cmd1[] = {
	0x03, 0x00, 0x39, 0xC0,
	0xF0, 0x5A, 0x5A, 0xFF,
};
static char sergej_on_cmd2[] = { 0xF2, 0x63, 0x15, 0x80 };
static char sergej_on_cmd3[] = {
	0x07, 0x00, 0x39, 0xC0,
	0xBD, 0x11, 0x01, 0x02,
	0x16, 0x02, 0x16, 0xFF,
};
/* level 2 lock, then 23 ms */
static char sergej_on_cmd4[] = {
	0x03, 0x00, 0x39, 0xC0,
	0xF0, 0xA5, 0xA5, 0xFF,
};
/* write ctrl display: brightness control on */
static char sergej_on_cmd5[] = { 0x53, 0x20, 0x15, 0x80 };
/* display brightness */
static char sergej_on_cmd6[] = { 0x51, 0x80, 0x15, 0x80 };
/* tear on */
static char sergej_on_cmd7[] = { 0x35, 0x00, 0x15, 0x80 };
/* display on */
static char sergej_on_cmd8[] = { 0x29, 0x00, 0x05, 0x80 };

static struct mipi_dsi_cmd sergej_wqhd_dualdsi_cmd_on_command[] = {
	{ sizeof(sergej_on_cmd0), sergej_on_cmd0, 5 },
	{ sizeof(sergej_on_cmd1), sergej_on_cmd1, 0 },
	{ sizeof(sergej_on_cmd2), sergej_on_cmd2, 0 },
	{ sizeof(sergej_on_cmd3), sergej_on_cmd3, 0 },
	{ sizeof(sergej_on_cmd4), sergej_on_cmd4, 23 },
	{ sizeof(sergej_on_cmd5), sergej_on_cmd5, 0 },
	{ sizeof(sergej_on_cmd6), sergej_on_cmd6, 0 },
	{ sizeof(sergej_on_cmd7), sergej_on_cmd7, 0 },
	{ sizeof(sergej_on_cmd8), sergej_on_cmd8, 0 },
};

/* display off, 33 ms; enter sleep, 120 ms */
static char sergej_off_cmd0[] = { 0x28, 0x00, 0x05, 0x80 };
static char sergej_off_cmd1[] = { 0x10, 0x00, 0x05, 0x80 };

static struct mipi_dsi_cmd sergej_wqhd_dualdsi_cmd_off_command[] = {
	{ sizeof(sergej_off_cmd0), sergej_off_cmd0, 33 },
	{ sizeof(sergej_off_cmd1), sergej_off_cmd1, 120 },
};

/* on commands in LP mode, off commands in HS mode */
static struct command_state sergej_wqhd_dualdsi_cmd_state = {
	0, 1
};

/*
 * TE check on, TE pin, TE from the pin, wr_mem_start 0x2c, DCS tear command.
 * Autorefresh on, every vsync: LK only kicks a command mode panel once
 * (fbcon_flush has no update_start for DSI), so without it the menu drawn
 * after the first frame never reaches the panel.
 */
static struct commandpanel_info sergej_wqhd_dualdsi_cmd_command_panel = {
	1, 1, 1, 1, 1, 0x2c, 0, 0, 0, 1, 0, 0
};

/* hsync pulse 32, bllp/eof power modes, burst traffic */
static struct videopanel_info sergej_wqhd_dualdsi_cmd_video_panel = {
	0, 0, 0, 0, 1, 1, 2, 0, 0
};

/* 4 lanes, lane_map_0123, all lanes on, clock lane HS */
static struct lane_configuration sergej_wqhd_dualdsi_cmd_lane_config = {
	4, 0, 1, 1, 1, 1, 1
};

static const uint32_t sergej_wqhd_dualdsi_cmd_timings[] = {
	0x97, 0x5A, 0x3E, 0x00, 0x9A, 0x9A, 0x48, 0x5E, 0x4B, 0x03, 0x04, 0x00
};

/* mdp trigger none, dma trigger sw, t_clk_post 0x05, t_clk_pre 0x5e */
static struct panel_timing sergej_wqhd_dualdsi_cmd_timing_info = {
	0x0, 0x04, 0x05, 0x5e
};

/* reset: high 17 ms, low 17 ms, high 17 ms */
static struct panel_reset_sequence sergej_wqhd_dualdsi_cmd_reset_seq = {
	{ 1, 0, 1, }, { 17, 17, 17, }, 2
};

/* brightness is set by the on commands (DCS 0x51) */
static struct backlight sergej_wqhd_dualdsi_cmd_backlight = {
	BL_DCS, 1, 255, 100, 2, "BL_CTL_DCS"
};

/* PMI8994 LAB/IBB in AMOLED mode, same voltages as the kernel (oled mode) */
static struct labibb_desc sergej_wqhd_dualdsi_cmd_labibb = {
	1, 1, 4000000, 4000000, 4600000, 4600000, 3, 3, 1, 0
};

static inline void panel_sergej_wqhd_dualdsi_cmd_select(struct panel_struct *panel,
							struct msm_panel_info *pinfo,
							struct mdss_dsi_phy_ctrl *phy_db)
{
	panel->paneldata = &sergej_wqhd_dualdsi_cmd_panel_data;
	panel->panelres = &sergej_wqhd_dualdsi_cmd_panel_res;
	panel->color = &sergej_wqhd_dualdsi_cmd_color;
	panel->videopanel = &sergej_wqhd_dualdsi_cmd_video_panel;
	panel->commandpanel = &sergej_wqhd_dualdsi_cmd_command_panel;
	panel->state = &sergej_wqhd_dualdsi_cmd_state;
	panel->laneconfig = &sergej_wqhd_dualdsi_cmd_lane_config;
	panel->paneltiminginfo = &sergej_wqhd_dualdsi_cmd_timing_info;
	panel->panelresetseq = &sergej_wqhd_dualdsi_cmd_reset_seq;
	panel->backlightinfo = &sergej_wqhd_dualdsi_cmd_backlight;
	pinfo->lcd_reg_en = 0;
	pinfo->labibb = &sergej_wqhd_dualdsi_cmd_labibb;
	pinfo->mipi.panel_on_cmds = sergej_wqhd_dualdsi_cmd_on_command;
	pinfo->mipi.panel_off_cmds = sergej_wqhd_dualdsi_cmd_off_command;
	pinfo->mipi.num_of_panel_on_cmds = ARRAY_SIZE(sergej_wqhd_dualdsi_cmd_on_command);
	pinfo->mipi.num_of_panel_off_cmds = ARRAY_SIZE(sergej_wqhd_dualdsi_cmd_off_command);
	memcpy(phy_db->timing, sergej_wqhd_dualdsi_cmd_timings, TIMING_SIZE);
	/* set by target/msm8994/oem_panel.c, which lk2nd panel mode leaves out */
	phy_db->pll_type = DSI_PLL_TYPE_20NM;
	/* cityman DT: qcom,regulator-ldo-mode */
	phy_db->regulator_mode = DSI_PHY_REGULATOR_LDO_MODE;
}

#endif /* _PANEL_SERGEJ_WQHD_DUALDSI_CMD_H_ */
