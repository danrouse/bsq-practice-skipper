# Builds a .zip file for loading with BMBF
& $PSScriptRoot/build.ps1

if ($?) {
    Compress-Archive -Path "./libs/arm64-v8a/libpractice_skipper.so", `
        "./libs/arm64-v8a/libbeatsaber-hook_0_8_4.so", `
        "./libs/arm64-v8a/libcustom-types.so", `
        "./libs/arm64-v8a/libquestui.so", `
        "./bmbfmod.json" `
        -DestinationPath "./practice_skipper_v1.0.0.zip" -Update
}
