{
  description = "raupeka compiler";
  license = "MIT";
  platforms = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];



  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/release-23.05";

  };

  eachSystem = with nixpkgs.lib; f: foldAttrs mergeAttrs { } 
    (map (s: mapAttrs (_: v: { ${s} = v; }) (f s)) systems);

  outputs = inputs@{self, nixpkgs, ...}: eachSystem ["aarch64-darwin" "x86_64-darwin" "x86_64-linux" "aarch64-linux" ] {
    stdenv.mkDerivation {
      name = "raupeka";
      src = ./.;

      buildInputs = with pkgs; [ 
        llvmPackages_13.bintools
        llvmPackages_11.clang
        llvmPackages_13.libclang
        llvmPackages_13.libcxx
        llvmPackages_13.libcxxabi
        llvmPackages_13.libcxxClang
        llvmPackages_13.libcxxStdenv
        llvmPackages_13.libllvm
        llvmPackages_13.llvm
        llvmPackages_13.openmp
        llvmPackages_13.stdenv 
        libxml2
        boost 
        bear 
        cmake
      ];
    };
  };
}
