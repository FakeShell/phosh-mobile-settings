/*
 * Copyright (C) 2023 Bardia Moshiri <fakeshell@bardia.tech>
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#define G_LOG_DOMAIN "ms-mtp-panel"

#include "mobile-settings-config.h"
#include "ms-mtp-panel.h"
#include "ms-util.h"

#include <glib/gi18n.h>

struct _MsMtpPanel {
  AdwBin            parent;
  GtkWidget        *mtp_enabled_switch;
};

G_DEFINE_TYPE (MsMtpPanel, ms_mtp_panel, ADW_TYPE_BIN)

static void
ms_mtp_panel_finalize (GObject *object)
{
  MsMtpPanel *self = MS_MTP_PANEL (object);

  G_OBJECT_CLASS (ms_mtp_panel_parent_class)->finalize (object);
}

static gboolean
ms_mtp_panel_enable_mtp(GtkSwitch *widget, gboolean state, MsMtpPanel *self) {
  GError *error = NULL;

  if(state) {
    system("rm -f ~/.mtp_disable");
    system("systemctl --user start mtp-server");
  } else {
    system("touch ~/.mtp_disable");
    system("systemctl --user stop mtp-server");
  }

  return FALSE;
}

static void
ms_mtp_panel_class_init (MsMtpPanelClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  object_class->finalize = ms_mtp_panel_finalize;

  gtk_widget_class_set_template_from_resource (widget_class,
                                               "/org/sigxcpu/MobileSettings/ui/ms-mtp-panel.ui");
  gtk_widget_class_bind_template_child (widget_class,
                                        MsMtpPanel,
                                        mtp_enabled_switch);
}

static void
ms_mtp_panel_init (MsMtpPanel *self)
{
  gtk_widget_init_template (GTK_WIDGET (self));
  
  gchar *output;
  gchar *error;
  gint exit_status;
  g_spawn_command_line_sync("systemctl is-active usb-tethering", &output, &error, &exit_status, NULL);

  if(g_str_has_prefix(output, "active")) {
      gtk_widget_set_sensitive(GTK_WIDGET(self->mtp_enabled_switch), FALSE);
  } else {
      if(g_file_test("/usr/bin/mtp-server", G_FILE_TEST_EXISTS)) {
          g_signal_connect(G_OBJECT(self->mtp_enabled_switch), "state-set", G_CALLBACK(ms_mtp_panel_enable_mtp), self);
      } else {
          gtk_widget_set_sensitive(GTK_WIDGET(self->mtp_enabled_switch), FALSE);
      }
  }
}

MsMtpPanel *
ms_mtp_panel_new (void)
{
  return MS_MTP_PANEL (g_object_new (MS_TYPE_MTP_PANEL, NULL));
}
