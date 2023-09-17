{
  description = "Lilly's Raupeka compiler";

  inputs = { nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable"; };

  outputs = inputs@{ flake-parts, nixpkgs, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      imports = [
        # To import a flake module
        # 1. Add foo to inputs
        # 2. Add foo as a parameter to the outputs function
        # 3. Add here: foo.flakeModule

      ];
      systems =
        [ "x86_64-linux" "aarch64-linux" "aarch64-darwin" "x86_64-darwin" ];
      perSystem = { config, self', inputs', pkgs, system, ... }: {
        # Per-system attributes can be defined here. The self' and inputs'
        # module parameters provide easy access to attributes of the same
        # system.

        # Equivalent to  inputs'.nixpkgs.legacyPackages.hello;
        packages.default = pkgs.stdenv.mkDerivation {
          name = "lrc";
          license = "MIT";
          src = ./.;

          buildInputs = with pkgs; [
            llvmPackages_13.bintools
            llvmPackages_13.clang
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
      flake = {
        # The usual flake attributes can be defined here, including system-
        # agnostic ones like nixosModule and system-enumerating ones, although
        # those are more easily expressed in perSystem.

      };
    };
}