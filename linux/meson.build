swarg = ''

if sizeof['long'] == 8
  archarg = '64'
else
  archarg = '32'
endif
meson.add_install_script('install.sh', meson.project_name() + '.' + host_machine.cpu(), archarg, swarg)

