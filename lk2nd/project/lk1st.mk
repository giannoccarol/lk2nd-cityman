# SPDX-License-Identifier: BSD-3-Clause
LK2ND_PROJECT := lk1st
LK2ND_DISPLAY ?= cont-splash
include lk2nd/project/base.mk

# Lumia 950 XL with the native panel driver: use the lk2nd menu, as lk1st
# upstream does, instead of the Qualcomm fastboot screen.
ifeq ($(LK2ND_DISPLAY),sergej_wqhd_dualdsi_cmd)
ENABLE_FBCON_DISPLAY_MSG ?= 0
endif
ENABLE_FBCON_DISPLAY_MSG ?= 1

# The device module is useless on lk1st if no DTB is bundled
ifneq ($(LK2ND_BUNDLE_DTB),)
MODULES += lk2nd/device
ifneq ($(ENABLE_FBCON_DISPLAY_MSG),1)
MODULES += $(if $(filter $(MODULES), lk2nd/display), lk2nd/device/menu)
endif
else
$(info NOTE: Device module is disabled without bundling a device DTB (LK2ND_BUNDLE_DTB))
endif
