win = import('windows')

res = files(
'resource.h',
'icon.ico',
'resource.rc'
)

windows_resources = win.compile_resources('resource.rc', depend_files: res)

meson.add_install_script('install.sh', meson.project_name() + '.exe')