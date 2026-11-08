project(
    'dsprot',
    ['c', 'nasm'],
    version: '1.23',
    meson_version: '>=1.12.0',
    default_options: ['buildtype=plain', 'warning_level=0'],
)


############################################################
###                         TOOLS                        ###
############################################################
subdir('tools')

############################################################
###                         COMPILERS                    ###
############################################################
mwccarm = meson.get_compiler('c', native: false).cmd_array()
mwasmarm = meson.get_compiler('nasm', native: false).cmd_array()

############################################################
###                         PROGRAMS                     ###
############################################################
python = import('python').find_installation()


############################################################
###                    INCLUDE PATHS                     ###
############################################################
include_dir = meson.project_source_root() / 'include'


############################################################
###                    COMPILER FLAGS                    ###
############################################################
c_args = []
asm_args = []
link_args = []

mwrap_sdk = get_option('mwrap_sdk')
if mwrap_sdk != 'default'
    c_args += ['-wrap:sdk', mwrap_sdk]
    asm_args += ['-wrap:sdk', mwrap_sdk]
    link_args += ['-wrap:sdk', mwrap_sdk]
endif

c_args += [
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

asm_args += [
    '-proc',
    'arm5TE',
]

link_args += [
    '-nostdlib',
    '-library',
]

dep_args = [
    '-gccdep',
    '-MD',
]

############################################################
###                       KEYS                           ###
############################################################
key_dsprot_main = '6AB2'
key_integrity = '9785'
key_core_tests = '0982'


############################################################
###                       DSPROT MAIN                    ###
############################################################
dsprot_main = custom_target(
    'dsprot_main',
    output: 'dsprot_main.o',
    depfile: '@BASENAME@.d',
    input: 'src/dsprot_main.c',
    command: [
        mwccarm,
        c_args,
        '-i',
        include_dir,
        dep_args,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

dsprot_main_encrypted = custom_target(
    'dsprot_main_encrypted',
    input: dsprot_main,
    output: 'dsprot_main_encrypted.o',
    command: [
        python,
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

dsprot_main_decrypter = custom_target(
    'dsprot_main_decrypter',
    output: 'dsprot_main_decrypter.s',
    input: dsprot_main_encrypted,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT@',
        '-k',
        key_dsprot_main,
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
)

dsprot_main_decrypter_obj = custom_target(
    'dsprot_main_decrypter_obj',
    output: 'dsprot_main_decrypter.o',
    input: dsprot_main_decrypter,
    command: [
        mwasmarm,
        asm_args,
        '-i',
        include_dir,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

dsprot_main_decrypter_encoded = custom_target(
    'dsprot_main_decrypter_encoded',
    input: dsprot_main_decrypter_obj,
    output: 'dsprot_main_decrypter_encoded.o',
    command: [
        python,
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

dsprot_main_decrypter_decoder = custom_target(
    'ds_prot_main_decroded',
    output: 'dsprot_main_decrypter_decoder.s',
    input: dsprot_main_decrypter_encoded,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT@',
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
)

dsprot_main_decrypter_decoder_obj = custom_target(
    'dsprot_main_decrypter_decoder_obj',
    output: 'dsprot_main_decrypter_decoder.o',
    input: dsprot_main_decrypter_decoder,
    command: [
        mwasmarm,
        asm_args,
        '-i',
        include_dir,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

############################################################
###                       EXTRA                          ###
############################################################
extra = custom_target(
    'extra',
    output: 'extra.o',
    depfile: '@BASENAME@.d',
    input: 'src/extra.c',
    command: [
        mwccarm,
        c_args,
        '-i',
        include_dir,
        dep_args,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

############################################################
###                       INTEGRITY                      ###
############################################################
integrity = custom_target(
    'integrity',
    output: 'integrity.o',
    depfile: '@BASENAME@.d',
    input: 'src/integrity.c',
    command: [
        mwccarm,
        c_args,
        '-i',
        include_dir,
        dep_args,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

integrity_encrypted = custom_target(
    'integrity_encrypted',
    input: integrity,
    output: 'integrity_encrypted.o',
    command: [
        python,
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

integrity_decrypter = custom_target(
    'integrity_decrypter',
    output: 'integrity_decrypter.s',
    input: integrity_encrypted,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT@',
        '-k',
        key_integrity,
        '-f',
        'Integrity_MACOwner_IsBad',
        'Integrity_MACOwner_IsGood',
        'Integrity_ROMTest_IsBad',
        'Integrity_ROMTest_IsGood',
    ],
)

integrity_decrypter_obj = custom_target(
    'integrity_decrypter_obj',
    output: 'integrity_decrypter.o',
    input: integrity_decrypter,
    command: [
        mwasmarm,
        asm_args,
        '-i',
        include_dir,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

integrity_decrypter_encoded = custom_target(
    'integrity_decrypter_encoded',
    input: integrity_decrypter_obj,
    output: 'integrity_decrypter_encoded.o',
    command: [
        python,
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

integrity_decrypter_decoder = custom_target(
    'integrity_decrypter_decoder',
    output: 'integrity_decrypter_decoder.s',
    input: integrity_decrypter_encoded,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT@',
        '-f',
        'RunEncrypted_Integrity_MACOwner_IsBad',
        'RunEncrypted_Integrity_MACOwner_IsGood',
        'RunEncrypted_Integrity_ROMTest_IsBad',
        'RunEncrypted_Integrity_ROMTest_IsGood',
    ],
)

integrity_decrypter_decoder_obj = custom_target(
    'integrity_decrypter_decoder_obj',
    output: 'integrity_decrypter_decoder.o',
    input: integrity_decrypter_decoder,
    command: [
        mwasmarm,
        asm_args,
        '-i',
        include_dir,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

############################################################
###                       ENCRYPTOR                      ###
############################################################
encryptor = custom_target(
    'encryptor',
    output: 'encryptor.o',
    depfile: '@BASENAME@.d',
    input: 'src/encryptor.c',
    command: [
        mwccarm,
        c_args,
        '-i',
        include_dir,
        dep_args,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

encryptor_encoded = custom_target(
    'encryptor_encoded',
    input: encryptor,
    output: 'encryptor_encoded.o',
    command: [
        python,
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

encryptor_decoder = custom_target(
    'encryptor_decoder',
    output: 'encryptor_decoder.s',
    input: encryptor_encoded,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT@',
        '-f',
        'Encryptor_EncryptFunction',
        'Encryptor_DecryptFunction',
    ],
)

encryptor_decoder_obj = custom_target(
    'encryptor_decoder_obj',
    output: 'encryptor_decoder.o',
    input: encryptor_decoder,
    command: [
        mwasmarm,
        asm_args,
        '-i',
        include_dir,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

############################################################
###                       MAC OWNER                      ###
############################################################
mac_owner = custom_target(
    'mac_owner',
    output: 'mac_owner.o',
    depfile: '@BASENAME@.d',
    input: 'src/mac_owner.c',
    command: [
        mwccarm,
        c_args,
        '-i',
        include_dir,
        dep_args,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

mac_owner_encrypted = custom_target(
    'mac_owner_encrypted',
    input: mac_owner,
    output: 'mac_owner_encrypted.o',
    command: [
        python,
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

mac_owner_decrypter = custom_target(
    'mac_owner_decrypter',
    output: 'mac_owner_decrypter.s',
    input: mac_owner_encrypted,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT@',
        '-k',
        key_core_tests,
        '-f',
        'MACOwner_IsBad',
        'MACOwner_IsGood',
    ],
)

mac_owner_decrypter_obj = custom_target(
    'mac_owner_decrypter_obj',
    output: 'mac_owner_decrypter.o',
    input: mac_owner_decrypter,
    command: [
        mwasmarm,
        asm_args,
        '-i',
        include_dir,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

mac_owner_decrypter_encoded = custom_target(
    'mac_owner_decrypter_encoded',
    input: mac_owner_decrypter_obj,
    output: 'mac_owner_decrypter_encoded.o',
    command: [
        python,
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

############################################################
###                       ROM UTIL                       ###
############################################################
rom_util = custom_target(
    'rom_util',
    output: 'rom_util.o',
    depfile: '@BASENAME@.d',
    input: 'src/rom_util.c',
    command: [
        mwccarm,
        c_args,
        '-i',
        include_dir,
        dep_args,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

rom_util_encrypted = custom_target(
    'rom_util_encrypted',
    input: rom_util,
    output: 'rom_util_encrypted.o',
    command: [
        python,
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

rom_util_decrypter = custom_target(
    'rom_util_decrypter',
    output: 'rom_util_decrypter.s',
    input: rom_util_encrypted,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT@',
        '-k',
        key_core_tests,
        '-f',
        'ROMUtil_Read',
        'ROMUtil_CRC32',
    ],
)

rom_util_decrypter_obj = custom_target(
    'rom_util_decrypter_obj',
    output: 'rom_util_decrypter.o',
    input: rom_util_decrypter,
    command: [
        mwasmarm,
        asm_args,
        '-i',
        include_dir,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

rom_util_decrypter_encoded = custom_target(
    'rom_util_decrypter_encoded',
    input: rom_util_decrypter_obj,
    output: 'rom_util_decrypter_encoded.o',
    command: [
        python,
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

############################################################
###                       ROM TEST                       ###
############################################################
rom_test = custom_target(
    'rom_test',
    output: 'rom_test.o',
    depfile: '@BASENAME@.d',
    input: 'src/rom_test.c',
    command: [
        mwccarm,
        c_args,
        '-i',
        include_dir,
        dep_args,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

rom_test_encrypted = custom_target(
    'rom_test_obj_copy',
    input: rom_test,
    output: 'rom_test_encrypted.o',
    command: [
        python,
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

rom_test_decrypter = custom_target(
    'rom_test_decrypter',
    output: 'rom_test_decrypter.s',
    input: rom_test_encrypted,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT@',
        '-k',
        key_core_tests,
        '-f',
        'ROMTest_IsBad',
        'ROMTest_IsGood',
    ],
)

rom_test_decrypter_obj = custom_target(
    'rom_test_decrypter_obj',
    output: 'rom_test_decrypter.o',
    input: rom_test_decrypter,
    command: [
        mwasmarm,
        asm_args,
        '-i',
        include_dir,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

rom_test_decrypter_encoded = custom_target(
    'rom_test_decrypter_encoded',
    input: rom_test_decrypter_obj,
    output: 'rom_test_decrypter_encoded.o',
    command: [
        python,
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)


############################################################
###                       CORETESTS                      ###
############################################################
coretests_decrypter_decoder = custom_target(
    'coretests_decrypter_decoder',
    output: 'coretests_decrypter_decoder.s',
    input: [
        mac_owner_decrypter_encoded,
        rom_util_decrypter_encoded,
        rom_test_decrypter_encoded,
    ],
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT@',
        '-f',
        'RunEncrypted_ROMTest_IsBad',
        'RunEncrypted_ROMTest_IsGood',
        'RunEncrypted_MACOwner_IsBad',
        'RunEncrypted_MACOwner_IsGood',
        'RunEncrypted_ROMUtil_Read',
        'RunEncrypted_ROMUtil_CRC32',
    ],
)

coretests_decrypter_decoder_obj = custom_target(
    'coretests_d_decrypter_decoder_obj',
    output: 'coretests_decrypter_decoder.o',
    input: coretests_decrypter_decoder,
    command: [
        mwasmarm,
        asm_args,
        '-i',
        include_dir,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

############################################################
###                       RC4                            ###
############################################################
rc4 = custom_target(
    'rc4',
    output: 'rc4.o',
    depfile: '@BASENAME@.d',
    input: 'src/rc4.c',
    command: [
        mwccarm,
        c_args,
        '-i',
        include_dir,
        dep_args,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

rc4_encoded = custom_target(
    'rc4_encoded',
    input: rc4,
    output: 'rc4_encoded.o',
    command: [
        python,
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

rc4_decoder = custom_target(
    'rc4_decoder',
    output: 'rc4_decoder.s',
    input: rc4_encoded,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT@',
        '-f',
        'RC4_Init',
        'RC4_Byte',
        'RC4_InitSBox',
        'RC4_EncryptInstructions',
        'RC4_DecryptInstructions',
        'RC4_InitAndEncryptInstructions',
        'RC4_InitAndDecryptInstructions',
    ],
)

rc4_decoder_obj = custom_target(
    'rc4_decoder_obj',
    output: 'rc4_decoder.o',
    input: rc4_decoder,
    command: [
        mwasmarm,
        asm_args,
        '-i',
        include_dir,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

############################################################
###                       LIBRARY                        ###
############################################################
dsprot = static_library(
    'dsprot',
    sources: [
        dsprot_main_encrypted,
        dsprot_main_decrypter_encoded,
        dsprot_main_decrypter_decoder_obj,
        extra,
        integrity_encrypted,
        integrity_decrypter_encoded,
        integrity_decrypter_decoder_obj,
        encryptor_encoded,
        encryptor_decoder_obj,
        mac_owner_encrypted,
        mac_owner_decrypter_encoded,
        rom_util_encrypted,
        rom_util_decrypter_encoded,
        rom_test_encrypted,
        rom_test_decrypter_encoded,
        coretests_decrypter_decoder_obj,
        rc4_encoded,
        rc4_decoder_obj,
    ],
    link_args: link_args,
    native: false,
)

############################################################
###                    FOR CONSUMERS                     ###
############################################################
libdsprot_dep = declare_dependency(link_with: dsprot)

meson.override_dependency('libdsprot', libdsprot_dep)
