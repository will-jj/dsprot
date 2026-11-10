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


dsprot_main_enc_decrypter = custom_target(
    'dsprot_main_enc_decrypter',
    output: ['dsprot_main_decrypter.s', 'dsprot_main.enc.o'],
    input: dsprot_main,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
        '--create-copy',
        '@OUTPUT1@',
        dsprot_main_decrypter_args,
    ],
    build_always: true,
)

dsprot_main_decrypter = dsprot_main_enc_decrypter[0]
dsprot_main_encrypted = dsprot_main_enc_decrypter[1]
message(dsprot_main_decrypter.full_path())
message(dsprot_main_encrypted.full_path())
