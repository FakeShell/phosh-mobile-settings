/*
 * Copyright (C) 2023 Bardia Moshiri <fakeshell@bardia.tech>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <adwaita.h>

G_BEGIN_DECLS

#define MS_TYPE_MTP_PANEL (ms_mtp_panel_get_type ())

G_DECLARE_FINAL_TYPE (MsMtpPanel, ms_mtp_panel, MS, MTP_PANEL, AdwBin)

MsMtpPanel *ms_mtp_panel_new (void);

G_END_DECLS
