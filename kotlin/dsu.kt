private class DSU(n: Int) {
    val p = IntArray(n) { it }
    val size = IntArray(n) { 0 }
    fun get(x: Int) : Int = when {
        p[x] == x -> x
        else -> get(p[x]).also { p[x] = it }
    }
    fun join(a:Int, b: Int) {
        val aa = get(a)
        val bb = get(b)
        if (size[aa] < size[bb]) {
            p[aa] = bb
            size[bb] += size[aa]
        } else {
            p[bb] = aa
            size[aa] += size[bb]
        }
    }
}
