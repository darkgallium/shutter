# Maintainer: darkgallium
pkgname=shutter
pkgver=1
pkgrel=1
pkgdesc="A simple screenshot tool for UI allergic people"
arch=('x86_64')
url="https://github.com/darkgallium/shutter"
license=('GPL')
groups=()
depends=('gtk3')
makedepends=('git')
provides=("${pkgname%-git}")
conflicts=("${pkgname%-git}")
replaces=()
backup=()
options=()
install=
source=('git+https://github.com/darkgallium/shutter.git')
noextract=()
md5sums=('SKIP')

build() {
	cd "$srcdir/${pkgname%-git}"
	make
}

package() {
	cd "$srcdir/${pkgname%-git}"
	make DESTDIR="$pkgdir/" install
}
