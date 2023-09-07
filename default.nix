let pkgs = import <nixpkgs> {};
    stdenv  = pkgs.llvmPackages_16.stdenv;
in

stdenv.mkDerivation {
  name = "raupeka";
  src = ./.;

  buildInputs = with pkgs; [ llvmPackages_16.libllvm boost ];

  buildPhase = "c++ -o main src/main.cpp -lllvm -lboost_system";

  installPhase = ''
    mkdir -p $out/bin
    cp main $out/bin/
  '';
}