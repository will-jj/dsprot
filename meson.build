project(
    'dsprot',
    ['c', 'cpp', 'nasm'],
    version: '1.0',
    meson_version: '>=1.12.0',
    default_options: ['buildtype=plain', 'warning_level=0'],
)
subdir('tools')

incdir = include_directories('include')
inc_dir_custom = meson.project_source_root() / 'include'

mwccarm = find_program('c', native: false)
mwasmarm = find_program('nasm', native: false)
mwldarm = find_program('c_ld', native: false)

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

asm_args = [
    '-proc',
    'arm5TE',
]

link_args = [
    '-nostdlib',
    '-library',
]

key_dsprot_main = '6AB2'
key_integrity = '9785'
key_core_tests = '0982'


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
dsprot_main_encrypted = custom_target(
    'dsprot_main_encrypted',
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
    input: dsprot_main_encrypted,
    command: [
        elfcoder_exe,
        '-e',
        '-i',
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
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
        inc_dir_custom,
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
)

dsprot_main_decrypter_encoded = custom_target(
    'dsprot_main_decrypter_encoded',
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
    input: dsprot_main_decrypter_encoded,
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
)

########### extra ###########

extra = custom_target(
    'extra',
    output: ['extra.o', 'extra.d'],
    input: 'src/extra.c',
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
)

########### integrity ###########

integrity = custom_target(
    'integrity',
    output: ['integrity.o', 'integrity.d'],
    input: 'src/integrity.c',
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
)

integrity_encrypted = custom_target(
    'integrity_encrypted',
    input: integrity[0],
    output: 'integrity_encrypted.o',
    command: [
        'python',
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
        '@OUTPUT0@',
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
        inc_dir_custom,
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
)

integrity_decrypter_encoded = custom_target(
    'integrity_decrypter_encoded',
    input: integrity_decrypter_obj,
    output: 'integrity_decrypter_encoded.o',
    command: [
        'python',
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
        '@OUTPUT0@',
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
        inc_dir_custom,
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
)

########### encryptor ###########

encryptor = custom_target(
    'encryptor',
    output: ['encryptor.o', 'encryptor.d'],
    input: 'src/encryptor.c',
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
)

encryptor_encoded = custom_target(
    'encryptor_encoded',
    input: encryptor[0],
    output: 'encryptor_encoded.o',
    command: [
        'python',
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
        '@OUTPUT0@',
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
        inc_dir_custom,
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
)

########### mac_owner ###########

mac_owner = custom_target(
    'mac_owner',
    output: ['mac_owner.o', 'mac_owner.d'],
    input: 'src/mac_owner.c',
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
)

mac_owner_encrypted = custom_target(
    'mac_owner_encrypted',
    input: mac_owner[0],
    output: 'mac_owner_encrypted.o',
    command: [
        'python',
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
        '@OUTPUT0@',
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
        inc_dir_custom,
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
)

mac_owner_decrypter_encoded = custom_target(
    'mac_owner_decrypter_encoded',
    input: mac_owner_decrypter_obj,
    output: 'mac_owner_decrypter_encoded.o',
    command: [
        'python',
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

########### rom_util ###########

rom_util = custom_target(
    'rom_util',
    output: ['rom_util.o', 'rom_util.d'],
    input: 'src/rom_util.c',
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
)

rom_util_encrypted = custom_target(
    'rom_util_encrypted',
    input: rom_util[0],
    output: 'rom_util_encrypted.o',
    command: [
        'python',
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
        '@OUTPUT0@',
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
        inc_dir_custom,
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
)

rom_util_decrypter_encoded = custom_target(
    'rom_util_decrypter_encoded',
    input: rom_util_decrypter_obj,
    output: 'rom_util_decrypter_encoded.o',
    command: [
        'python',
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

########### rom_test ###########

rom_test = custom_target(
    'rom_test',
    output: ['rom_test.o', 'rom_test.d'],
    input: 'src/rom_test.c',
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
)

rom_test_encrypted = custom_target(
    'rom_test_obj_copy',
    input: rom_test[0],
    output: 'rom_test_encrypted.o',
    command: [
        'python',
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
        '@OUTPUT0@',
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
        inc_dir_custom,
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
)

rom_test_decrypter_encoded = custom_target(
    'rom_test_decrypter_encoded',
    input: rom_test_decrypter_obj,
    output: 'rom_test_decrypter_encoded.o',
    command: [
        'python',
        '-c',
        'import shutil,sys; shutil.copyfile(sys.argv[1], sys.argv[2])',
        '@INPUT@',
        '@OUTPUT@',
    ],
)

########### coretests ###########

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
        '@OUTPUT0@',
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
        inc_dir_custom,
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
)

########### rc4 ###########

rc4 = custom_target(
    'rc4',
    output: ['rc4.o', 'rc4.d'],
    input: 'src/rc4.c',
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
)

rc4_encoded = custom_target(
    'rc4_encoded',
    input: rc4[0],
    output: 'rc4_encoded.o',
    command: [
        'python',
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
        '@OUTPUT0@',
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
        inc_dir_custom,
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
)

########### library ###########

dsprot = custom_target(
    'dsprot',
    output: 'dsprot.a',
    input: [
        dsprot_main_encrypted,
        dsprot_main_decrypter_decoder_obj,
        dsprot_main_decrypter_decoder_obj,
        extra[0],
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
    command: [
        mwldarm,
        link_args,
        '@INPUT@',
        '-o',
        '@OUTPUT0@',
    ],
    build_by_default: true,
)
