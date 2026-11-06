project(
    'dsprot',
    ['c', 'cpp', 'nasm'],
    version: '1.0',
    meson_version: '>=1.12.0',
    default_options: ['buildtype=plain', 'warning_level=0'],
)
asm_args = [
    '-proc',
    'arm5TE',
]


subdir('tools')

incdir = include_directories('include')
inc_dir_custom = meson.project_source_root() / 'include'
mwccarm = meson.get_compiler('c', native: false).cmd_array()
mwasmarm = meson.get_compiler('nasm', native: false).cmd_array()


c_args = [
    '-O4,p',
    '-enum',
    'int',
    '-proc',
    'arm946E',
    '-gccext,on',
    '-fp',
    'soft',
    '-lang',
    'c99',
    '-char',
    'signed',
    '-inline',
    'on,noauto',
    '-Cpp_exceptions',
    'off',
    '-interworking',
    '-c',
    '-W',
    'all',
    '-W',
    'pedantic',
    '-W',
    'noimpl_signedunsigned',
    '-W',
    'noimplicitconv',
    '-W',
    'nounusedarg',
    '-W',
    'nomissingreturn',
    '-W',
    'error',
]

libo_args = [
    '-O4,p',
    '-enum',
    'int',
    '-proc',
    'arm946E',
    '-gccext,on',
    '-fp',
    'soft',
    '-lang',
    'c99',
    '-char',
    'signed',
    '-inline',
    'on,noauto',
    '-Cpp_exceptions',
    'off',
    '-interworking',
    '-c',
    '-W',
    'all',
    '-W',
    'pedantic',
    '-W',
    'noimpl_signedunsigned',
    '-W',
    'noimplicitconv',
    '-W',
    'nounusedarg',
    '-W',
    'nomissingreturn',
    '-W',
    'error',
]

nasm_args = [asm_args]

link_args = [
    '-nostdlib',
    '-library',
]


dsprot_main = custom_target(
    'dsprot_main',
    output: ['dsprot_main.o', 'dsprot_main.d'],
    input: 'src/dsprot_main.c',
    command: [
        mwccarm,
        c_args,
        '-i',
        inc_dir_custom,
        '-gccdep',
        '-MD',
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
    build_by_default: true,
)

# This is hacky as the file is actually written over and output is not used
#my_ds_proc_fd = custom_target('dsprot_main_fd',
#  output : 'dsprot_main.fix.d',
#  input  : ds_proc[1],
#  command : [fixdep_exe, '@INPUT@'],
#  build_by_default : true,
#)

location = 'dsprot_main' + '_encrypted.o'

# this causes a warning of hard error
#copy = fs.copyfile(dsprot_main[0].full_path(), location)

# this seems cursed
dsprot_main_obj_copy = custom_target(
    'dsprot_main_obj_copy',
    input: dsprot_main[0],
    output: 'dsprot_main_encrypted.o',
    command: [
        'python',
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

dsprot_main_decrypter = custom_target(
    'dsprot_main_decrypter',
    output: 'dsprot_main_decrypter.s',
    input: dsprot_main_obj_copy,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
        '-k',
        '6AB2',
        '-p',
        'DSProt_',
        '-f',
        'DetectFlashcart',
        'DetectNotFlashcart',
        'DetectEmulator',
        'DetectNotEmulator',
        'DetectDummy',
        'DetectNotDummy',
    ],
    build_by_default: true,
)

dsprot_main_decrypter_obj = custom_target(
    'dsprot_main_decrypter_obj',
    output: 'dsprot_main_decrypter.o',
    input: dsprot_main_decrypter,
    command: [
        mwasmarm,
        asm_args,
        '-i',
        inc_dir_custom,
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
    build_by_default: true,
)

dsprot_main_decrypter_obj_copy = custom_target(
    'dsprot_main_decrypter_obj_copy',
    input: dsprot_main_decrypter_obj,
    output: 'dsprot_main_decrypter_encoded.o',
    command: [
        'python',
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

dsprot_main_decrypter_decoder = custom_target(
    'ds_prot_main_decroded',
    output: 'dsprot_main_decrypter_decoder.s',
    input: dsprot_main_decrypter_obj_copy,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
        '-g',
        'Garbage',
        '-f',
        'DSProt_DetectFlashcart',
        'DSProt_DetectNotFlashcart',
        'DSProt_DetectEmulator',
        'DSProt_DetectNotEmulator',
        'DSProt_DetectDummy',
        'DSProt_DetectNotDummy',
    ],
    build_by_default: true,
)

dsprot_main_decrypter_decoder_obj = custom_target(
    'dsprot_main_decrypter_decoder_obj',
    output: 'dsprot_main_decrypter_decoder.o',
    input: dsprot_main_decrypter_decoder,
    command: [
        mwasmarm,
        asm_args,
        '-i',
        inc_dir_custom,
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
    build_by_default: true,
)