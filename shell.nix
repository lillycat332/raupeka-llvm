let pkgs = import<nixpkgs>{};
in
pkgs.mkShell.override { stdenv = pkgs.llvmPackages_16.stdenv; } {
  nativeBuildInputs = with pkgs; [
    llvmPackages_16.libllvm
    llvmPackages_16.clang
  ];
}
