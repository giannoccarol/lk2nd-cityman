# SPDX-License-Identifier: BSD-3-Clause
LOCAL_DIR := $(GET_LOCAL_DIR)

# Filter out original panel implementation
OBJS := $(filter-out target/$(TARGET)/oem_panel.o, $(OBJS))

OBJS += $(LOCAL_DIR)/oem_panel.o

# Lumia 950 XL (cityman): AMOLED power and TE pin handled in target/msm8994
ifeq ($(LK2ND_DISPLAY),sergej_wqhd_dualdsi_cmd)
DEFINES += LK2ND_PANEL_SERGEJ=1
endif
