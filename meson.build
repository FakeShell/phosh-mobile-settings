project('phosh-mobile-settings', 'c',
          version: '0.28.0',
    meson_version: '>= 0.58.0',
  default_options: [ 'warning_level=2',
                     'werror=false',
                     'c_std=gnu11',
                   ],
)

prefix = get_option('prefix')
datadir = join_paths(prefix, get_option('datadir'))
libdir = join_paths(prefix, get_option('libdir'))
ms_plugins_dir = join_paths(prefix, libdir, 'phosh-mobile-settings', 'plugins')

glib_ver = '2.66'
glib_ver_str = 'GLIB_VERSION_@0@'.format(glib_ver.replace('.','_'))
glib_ver_cmp = '>=@0@'.format(glib_ver)

glib_dep = dependency('glib-2.0', version: glib_ver_cmp)
gio_dep = dependency('gio-2.0', version: glib_ver_cmp)
gio_unix_dep =  dependency('gio-unix-2.0', version: glib_ver_cmp)
gmodule_dep = dependency('gmodule-2.0', version: glib_ver_cmp)
gsound_dep = dependency('gsound')
gtk_dep = dependency('gtk4', version: '>= 4.4')
gtk_wayland_dep = dependency('gtk4-wayland', version: '>= 4.4')
adwaita_dep = dependency('libadwaita-1', version: '>= 1.2')
phosh_plugins_dep = dependency('phosh-plugins', version: '>= 0.23.0')
wayland_client_dep = dependency('wayland-client', version: '>=1.14')
wayland_protos_dep = dependency('wayland-protocols', version: '>=1.12')

i18n = import('i18n')

gnome = import('gnome')

cc = meson.get_compiler('c')
global_c_args = []
test_c_args = [
  '-Wcast-align',
  '-Wdate-time',
  '-Wdeclaration-after-statement',
  ['-Werror=format-security', '-Werror=format=2'],
  '-Wendif-labels',
  '-Werror=incompatible-pointer-types',
  '-Werror=missing-declarations',
  '-Werror=overflow',
  '-Werror=return-type',
  '-Werror=shift-count-overflow',
  '-Werror=shift-overflow=2',
  '-Werror=implicit-fallthrough=3',
  '-Wfloat-equal',
  '-Wformat-nonliteral',
  '-Wformat-security',
  '-Winit-self',
  '-Wmaybe-uninitialized',
  '-Wmissing-field-initializers',
  '-Wmissing-include-dirs',
  '-Wmissing-noreturn',
  '-Wnested-externs',
  '-Wno-missing-field-initializers',
  '-Wno-sign-compare',
  '-Wno-strict-aliasing',
  '-Wno-unused-parameter',
  '-Wold-style-definition',
  '-Wpointer-arith',
  '-Wredundant-decls',
  '-Wshadow',
  '-Wstrict-prototypes',
  '-Wswitch-default',
  '-Wswitch-enum',
  '-Wtype-limits',
  '-Wundef',
  '-Wunused-function',
]
if get_option('buildtype') != 'plain'
  test_c_args += '-fstack-protector-strong'
endif

foreach arg: test_c_args
  if cc.has_multi_arguments(arg)
    global_c_args += arg
  endif
endforeach
add_project_arguments(
  global_c_args,
  language: 'c'
)

config_h = configuration_data()
config_h.set_quoted('PACKAGE_VERSION', meson.project_version())
config_h.set_quoted('GETTEXT_PACKAGE', 'phosh-mobile-settings')
config_h.set_quoted('LOCALEDIR', join_paths(get_option('prefix'), get_option('localedir')))
config_h.set_quoted('MOBILE_SETTINGS_APP_ID', 'org.sigxcpu.MobileSettings')
config_h.set_quoted('MOBILE_SETTINGS_VERSION', meson.project_version())
config_h.set_quoted('MOBILE_SETTINGS_PLUGINS_DIR', ms_plugins_dir)
config_h.set_quoted('MOBILE_SETTINGS_PHOSH_PLUGINS_DIR',
		    phosh_plugins_dep.get_variable(pkgconfig: 'lockscreen_plugins_dir'))
config_h.set_quoted('MOBILE_SETTINGS_PHOSH_PREFS_DIR',
		    phosh_plugins_dep.get_variable(pkgconfig: 'lockscreen_prefs_dir'))
configure_file(
  output: 'mobile-settings-config.h',
  configuration: config_h,
)
add_project_arguments([
  '-I' + meson.project_build_root(),
], language: 'c')


subdir('data')
subdir('protocols')
subdir('src')
subdir('plugins')
subdir('po')

# Older meson can't handle gnome.post_install but that only
# matters for distro backports:
if meson.version().version_compare('>=0.59.0')
  gnome.post_install(
    glib_compile_schemas: true,
    gtk_update_icon_cache: true,
    update_desktop_database: true,
  )
endif
