private const val COMB_MAX = $END$
private val fs = ModIntArray(COMB_MAX) { ModInt(1) }.apply {
    for (i in 1 until size) {
        set(i, get(i - 1) * ModInt.from(i))
    }
}
private val ifs = ModIntArray(COMB_MAX) { fs[it].inv() }

private fun cnk(n: Int, k: Int) = fs[n] * ifs[k] * ifs[n - k]

