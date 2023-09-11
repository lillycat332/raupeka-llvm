let pkgs = import<nixpkgs>{};
in
pkgs.mkShell {
  nativeBuildInputs = with pkgs; [
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
}
