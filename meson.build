project('dsprot', ['c', 'cpp'],
    version: '1.0',
    meson_version: '>=1.12.0',
    default_options : [
        'buildtype=plain',
        'warning_level=0'
    ]
)

asm_args = [
    '-proc', 'arm5TE',
]


subdir('tools')

dsprot_sources = [
  'src/dsprot_main.c',
  'src/encryptor.c',
  'src/extra.c',
  'src/integrity.c',
  'src/mac_owner.c',
  'src/rc4.c',
  'src/rom_test.c',
  'src/rom_util.c',
]


incdir = include_directories('include')

dsprot_lib = static_library('dsprot',
    dsprot_sources,
    c_args : [
        '-O4,p',
        '-enum', 'int',
        '-proc', 'arm946E',
        '-gccext,on',
        '-fp', 'soft',
        '-lang', 'c99',
        '-char', 'signed',
        '-inline', 'on,noauto',
        '-Cpp_exceptions', 'off',
        '-interworking',
        '-c',
        '-W', 'all',
        '-W', 'pedantic',
        '-W', 'noimpl_signedunsigned',
        '-W', 'noimplicitconv',
        '-W', 'nounusedarg',
        '-W', 'nomissingreturn',
        '-W', 'error',
    ],

    nasm_args : [
        asm_args
    ],

    link_args : [
        '-nostdlib',
        '-library',
    ],
    include_directories : incdir,
    native : false
)

