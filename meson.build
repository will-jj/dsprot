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
mwccarm = find_program('c', native: false)
mwasmarm = find_program('nasm', native: false)

############################################################
###                         PROGRAMS                     ###
############################################################
cp = find_program('cp')

############################################################
###                    INCLUDE PATHS                     ###
############################################################
include_dir = meson.project_source_root() / 'include'


############################################################
###                    COMPILER FLAGS                    ###
############################################################
c_args = []
asm_args = []

mwrap_sdk = get_option('mwrap_sdk')
if mwrap_sdk != 'default'
    c_args += ['-wrap:sdk', mwrap_sdk]
    asm_args += ['-wrap:sdk', mwrap_sdk]
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
###                       ENCODED FUNCTIONS              ###
############################################################
dsprot_main_decrypter_functions = [
    'DetectFlashcart',
    'DetectNotFlashcart',
    'DetectEmulator',
    'DetectNotEmulator',
    'DetectDummy',
    'DetectNotDummy',
]

dsprot_main_decrypter_decoder_functions = [
    'DSProt_DetectFlashcart',
    'DSProt_DetectNotFlashcart',
    'DSProt_DetectEmulator',
    'DSProt_DetectNotEmulator',
    'DSProt_DetectDummy',
    'DSProt_DetectNotDummy',
]

integrity_decrypter_functions = [
    'Integrity_MACOwner_IsBad',
    'Integrity_MACOwner_IsGood',
    'Integrity_ROMTest_IsBad',
    'Integrity_ROMTest_IsGood',
]

integrity_decrypter_decoder_functions = [
    'RunEncrypted_Integrity_MACOwner_IsBad',
    'RunEncrypted_Integrity_MACOwner_IsGood',
    'RunEncrypted_Integrity_ROMTest_IsBad',
    'RunEncrypted_Integrity_ROMTest_IsGood',
]

encryptor_decoder_functions = [
    'Encryptor_EncryptFunction',
    'Encryptor_DecryptFunction',
]

mac_owner_decrypter_functions = [
    'MACOwner_IsBad',
    'MACOwner_IsGood',
]

rom_util_decrypter_functions = [
    'ROMUtil_Read',
    'ROMUtil_CRC32',
]

rom_test_functions = [
    'ROMTest_IsBad',
    'ROMTest_IsGood',
]

coretests_decrypter_decoder_functions = [
    'RunEncrypted_ROMTest_IsBad',
    'RunEncrypted_ROMTest_IsGood',
    'RunEncrypted_MACOwner_IsBad',
    'RunEncrypted_MACOwner_IsGood',
    'RunEncrypted_ROMUtil_Read',
    'RunEncrypted_ROMUtil_CRC32',
]

rc4_decoder_functions = [
    'RC4_Init',
    'RC4_Byte',
    'RC4_InitSBox',
    'RC4_EncryptInstructions',
    'RC4_DecryptInstructions',
    'RC4_InitAndEncryptInstructions',
    'RC4_InitAndDecryptInstructions',
]

############################################################
###                       ENC ARGS                       ###
############################################################
dsprot_main_decrypter_args = [
    '-k',
    key_dsprot_main,
    '-p',
    'DSProt_',
    '-f',
    dsprot_main_decrypter_functions,
]

dsprot_main_decrypter_decoder_args = [
    '-g',
    'Garbage',
    '-f',
    dsprot_main_decrypter_decoder_functions,
]

integrity_decrypter_args = [
    '-k',
    key_integrity,
    '-f',
    integrity_decrypter_functions,
]


integrity_decrypter_decoder_args = [
    '-f',
    integrity_decrypter_decoder_functions,
]

encryptor_decoder_args = [
    '-f',
    encryptor_decoder_functions,
]

mac_owner_decrypter_args = [
    '-k',
    key_core_tests,
    '-f',
    mac_owner_decrypter_functions,
]

rom_util_decrypter_args = [
    '-k',
    key_core_tests,
    '-f',
    rom_util_decrypter_functions,
]

rom_test_decrypter_args = [
    '-k',
    key_core_tests,
    '-f',
    rom_test_functions,
]

coretests_decrypter_decoder_args = [
    '-f',
    coretests_decrypter_decoder_functions,
]

rc4_decoder_args = [
    '-f',
    rc4_decoder_functions,
]

############################################################
###                      .c -> .o                        ###
############################################################

mwccarm_gen = generator(
    mwccarm,
    output: '@BASENAME@.o',
    depfile: '@BASENAME@.d',
    arguments: [
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
###                      .s -> .o                        ###
############################################################

mwasmarm_gen = generator(
    mwasmarm,
    output: '@BASENAME@.o',
    arguments: [
        asm_args,
        '-i',
        include_dir,
        '@INPUT@',
        '-o',
        '@OUTPUT@',
    ],
)

############################################################
###                      ENCODE/ENCRYPT                  ###
############################################################
elfcoder_gen = generator(
    elfcoder_exe,
    output: '@BASENAME@_dec.s',
    arguments: [
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT@',
        '@EXTRA_ARGS@',
    ],
)

############################################################
###                       DSPROT MAIN                    ###
############################################################
dsprot_main = mwccarm_gen.process('src/dsprot_main.c')

dsprot_main_encrypted = custom_target(
    'dsprot_main_encrypted',
    input: dsprot_main,
    output: 'dsprot_main_encrypted.o',
    command: [
        'cp',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

dsprot_main_decrypter = elfcoder_gen.process(
    dsprot_main_encrypted,
    extra_args: dsprot_main_decrypter_args,
)

dsprot_main_decrypter_obj = mwasmarm_gen.process(dsprot_main_decrypter)

dsprot_main_decrypter_encoded = custom_target(
    'dsprot_main_decrypter_encoded',
    input: dsprot_main_decrypter_obj,
    output: 'dsprot_main_decrypter_encoded.o',
    command: [
        'cp',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

dsprot_main_decrypter_decoder = elfcoder_gen.process(
    dsprot_main_decrypter_encoded,
    extra_args: dsprot_main_decrypter_decoder_args,
)

dsprot_main_decrypter_decoder_obj = mwasmarm_gen.process(
    dsprot_main_decrypter_decoder,
)

############################################################
###                       EXTRA                          ###
############################################################
extra = mwccarm_gen.process('src/extra.c')

############################################################
###                       INTEGRITY                      ###
############################################################
integrity = mwccarm_gen.process('src/integrity.c')

integrity_encrypted = custom_target(
    'integrity_encrypted',
    input: integrity,
    output: 'integrity_encrypted.o',
    command: [
        'cp',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

integrity_decrypter = elfcoder_gen.process(
    integrity_encrypted,
    extra_args: integrity_decrypter_args,
)

integrity_decrypter_obj = mwasmarm_gen.process(integrity_decrypter)

integrity_decrypter_encoded = custom_target(
    'integrity_decrypter_encoded',
    input: integrity_decrypter_obj,
    output: 'integrity_decrypter_encoded.o',
    command: [
        'cp',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

integrity_decrypter_decoder = elfcoder_gen.process(
    integrity_decrypter_encoded,
    extra_args: integrity_decrypter_decoder_args,
)

integrity_decrypter_decoder_obj = mwasmarm_gen.process(
    integrity_decrypter_decoder,
)

############################################################
###                       ENCRYPTOR                      ###
############################################################
encryptor = mwccarm_gen.process('src/encryptor.c')

encryptor_encoded = custom_target(
    'encryptor_encoded',
    input: encryptor,
    output: 'encryptor_encoded.o',
    command: [
        'cp',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

encryptor_decoder = elfcoder_gen.process(
    encryptor_encoded,
    extra_args: encryptor_decoder_args,
)

encryptor_decoder_obj = mwasmarm_gen.process(encryptor_decoder)

############################################################
###                       MAC OWNER                      ###
############################################################
mac_owner = mwccarm_gen.process('src/mac_owner.c')


mac_owner_encrypted = custom_target(
    'mac_owner_encrypted',
    input: mac_owner,
    output: 'mac_owner_encrypted.o',
    command: [
        'cp',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

mac_owner_decrypter = elfcoder_gen.process(
    mac_owner_encrypted,
    extra_args: mac_owner_decrypter_args,
)

mac_owner_decrypter_obj = mwasmarm_gen.process(mac_owner_decrypter)

mac_owner_decrypter_encoded = custom_target(
    'mac_owner_decrypter_encoded',
    input: mac_owner_decrypter_obj,
    output: 'mac_owner_decrypter_encoded.o',
    command: [
        'cp',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

############################################################
###                       ROM UTIL                       ###
############################################################
rom_util = mwccarm_gen.process('src/rom_util.c')

rom_util_encrypted = custom_target(
    'rom_util_encrypted',
    input: rom_util,
    output: 'rom_util_encrypted.o',
    command: [
        'cp',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

rom_util_decrypter = elfcoder_gen.process(
    rom_util_encrypted,
    extra_args: rom_util_decrypter_args,
)

rom_util_decrypter_obj = mwasmarm_gen.process(rom_util_decrypter)

rom_util_decrypter_encoded = custom_target(
    'rom_util_decrypter_encoded',
    input: rom_util_decrypter_obj,
    output: 'rom_util_decrypter_encoded.o',
    command: [
        'cp',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

############################################################
###                       ROM TEST                       ###
############################################################
rom_test = mwccarm_gen.process('src/rom_test.c')

rom_test_encrypted = custom_target(
    'rom_test_obj_copy',
    input: rom_test,
    output: 'rom_test_encrypted.o',
    command: [
        'cp',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

rom_test_decrypter = elfcoder_gen.process(
    rom_test_encrypted,
    extra_args: rom_test_decrypter_args,
)

rom_test_decrypter_obj = mwasmarm_gen.process(rom_test_decrypter)


rom_test_decrypter_encoded = custom_target(
    'rom_test_decrypter_encoded',
    input: rom_test_decrypter_obj,
    output: 'rom_test_decrypter_encoded.o',
    command: [
        'cp',
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
        coretests_decrypter_decoder_args,
    ],
)

coretests_decrypter_decoder_obj = mwasmarm_gen.process(
    coretests_decrypter_decoder,
)

############################################################
###                       RC4                            ###
############################################################
rc4 = mwccarm_gen.process('src/rc4.c')

rc4_encoded = custom_target(
    'rc4_encoded',
    input: rc4,
    output: 'rc4_encoded.o',
    command: [
        'cp',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

rc4_decoder = elfcoder_gen.process(
    rc4_encoded,
    extra_args: rc4_decoder_args,
)

rc4_decoder_obj = mwasmarm_gen.process(rc4_decoder)

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
    native: false,
)

############################################################
###                    FOR CONSUMERS                     ###
############################################################
dsprot_dep = declare_dependency(link_with: dsprot)

meson.override_dependency('dsprot', dsprot_dep)

