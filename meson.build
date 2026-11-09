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
###                      .c -> o                         ###
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
###                      .s -> o                         ###
############################################################

mwasmarm_gen = generator(
    mwasmarm,
    output: '@BASENAME@.o',
    depfile: '@BASENAME@.d',
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
###                      COPY FOR ENCRYPT/ENCODING       ###
############################################################
copy_enc_gen = generator(
    cp,
    output: '@BASENAME@_enc.o',
    arguments: [
        '@INPUT@',
        '@OUTPUT@',
    ],
)

############################################################
###                       DSPROT MAIN                    ###
############################################################
dsprot_main = mwccarm_gen.process('src/dsprot_main.c')
dsprot_main_encrypted = copy_enc_gen.process(dsprot_main)


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
        dsprot_main_decrypter_functions,
    ],
)

dsprot_main_decrypter_obj = mwasmarm_gen.process(dsprot_main_decrypter)

dsprot_main_decrypter_encoded = copy_enc_gen.process(dsprot_main_decrypter_obj)

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
        dsprot_main_decrypter_decoder_functions,
    ],
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
integrity_encrypted = copy_enc_gen.process(integrity)

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
        integrity_decrypter_functions,
    ],
)

integrity_decrypter_obj = mwasmarm_gen.process(integrity_decrypter)

integrity_decrypter_encoded = copy_enc_gen.process(integrity_decrypter_obj)

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
        integrity_decrypter_decoder_functions,
    ],
)

integrity_decrypter_decoder_obj = mwasmarm_gen.process(
    integrity_decrypter_decoder,
)

############################################################
###                       ENCRYPTOR                      ###
############################################################
encryptor = mwccarm_gen.process('src/encryptor.c')
encryptor_encoded = copy_enc_gen.process(encryptor)


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
        encryptor_decoder_functions,
    ],
)

encryptor_decoder_obj = mwasmarm_gen.process(encryptor_decoder)

############################################################
###                       MAC OWNER                      ###
############################################################
mac_owner = mwccarm_gen.process('src/mac_owner.c')
mac_owner_encrypted = copy_enc_gen.process(mac_owner)


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
        mac_owner_decrypter_functions,
    ],
)

mac_owner_decrypter_obj = mwasmarm_gen.process(mac_owner_decrypter)
mac_owner_decrypter_encoded = copy_enc_gen.process(mac_owner_decrypter_obj)

############################################################
###                       ROM UTIL                       ###
############################################################
rom_util = mwccarm_gen.process('src/rom_util.c')
rom_util_encrypted = copy_enc_gen.process(rom_util)


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
        rom_util_decrypter_functions,
    ],
)
rom_util_decrypter_obj = mwasmarm_gen.process(rom_util_decrypter)
rom_util_decrypter_encoded = copy_enc_gen.process(rom_util_decrypter_obj)

############################################################
###                       ROM TEST                       ###
############################################################
rom_test = mwccarm_gen.process('src/rom_test.c')
rom_test_encrypted = copy_enc_gen.process(rom_test)

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
        rom_test_functions,
    ],
)

rom_test_decrypter_obj = mwasmarm_gen.process(rom_test_decrypter)
rom_test_decrypter_encoded = copy_enc_gen.process(rom_test_decrypter_obj)

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
        coretests_decrypter_decoder_functions,
    ],
)

coretests_decrypter_decoder_obj = mwasmarm_gen.process(
    coretests_decrypter_decoder,
)

############################################################
###                       RC4                            ###
############################################################
rc4 = mwccarm_gen.process('src/rc4.c')
rc4_encoded = copy_enc_gen.process(rc4)

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
        rc4_decoder_functions,
    ],
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
