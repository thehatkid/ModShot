global_sources += custom_target(
    input: ['ruby/rpgscript.rb', 'rgss'],
    output: 'xScripts.rxdata',
    command: [ruby, '@INPUT0@', '-s', '@INPUT1@', '-o', '@OUTPUT@']
)
