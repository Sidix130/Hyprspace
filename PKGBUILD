# Maintainer: Sidix130 https://github.com/Sidix130 - sidix.dev@gmail.com

pkgname=hyprspace-git
pkgver=r238.12cfe04
pkgrel=1
pkgdesc="A workspace overview plugin for Hyprland"
arch=('x86_64')
url="https://github.com/Sidix130/Hyprspace"
license=('BSD')
depends=('hyprland>=0.52.0' 'pixman' 'libdrm' 'cairo' 'pango')
makedepends=('git' 'make' 'gcc' 'pkg-config')
provides=("${pkgname%-git}")
conflicts=("${pkgname%-git}")
source=("git+https://github.com/Sidix130/Hyprspace.git")
sha256sums=('SKIP')

pkgver() {
    cd "${srcdir}/Hyprspace"
    printf "r%s.%s" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
    cd "${srcdir}/Hyprspace"
    make all
}

package() {
    cd "${srcdir}/Hyprspace"
    
    # Install the plugin
    install -Dm755 Hyprspace.so "${pkgdir}/usr/lib/hyprland/plugins/Hyprspace.so"
    
    # Install documentation
    install -Dm644 README.md "${pkgdir}/usr/share/doc/${pkgname}/README.md"
    
    # Install license if present
    if [ -f LICENSE ]; then
        install -Dm644 LICENSE "${pkgdir}/usr/share/licenses/${pkgname}/LICENSE"
    fi
}
