
THIS_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source $THIS_DIR/os.sh

if is_windows; then
	export vocabulary_deps="${HOME}/Projects"
else
	export vocabulary_deps="${HOME}/Projects"
fi

[ ! -z vocabulary_deps ] && build_deps=$vocabulary_deps
