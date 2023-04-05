@Suppress("NOTHING_TO_INLINE")
private class Hasher private constructor(val a: EncodedLongArray) {
    @JvmInline
    value class EncodedLong(val x: Long) {
        val f get() = (x and ((1L shl 32) - 1)).toInt()
        val s get() = (x shr 32).toInt()

        constructor(a: Int, b: Int) : this((a.toLong() shl 32) or b.toLong())

        operator fun plus(other: EncodedLong) = EncodedLong(addMod(f, other.f, MOD1), addMod(s, other.s, MOD2))
        operator fun minus(other: EncodedLong) = EncodedLong(subMod(f, other.f, MOD1), subMod(s, other.s, MOD2))
        operator fun times(other: EncodedLong) =
            EncodedLong((f.toLong() * other.f.toLong() % MOD1).toInt(), (s.toLong() * other.s.toLong() % MOD2).toInt())
    }

    @JvmInline
    value class EncodedLongArray(private val storage: LongArray) {
        operator fun get(index: Int) = EncodedLong(storage[index])
        operator fun set(index: Int, value: EncodedLong) {
            storage[index] = value.x
        }

        val size get() = storage.size
    }

    private val degs = EncodedLongArray(a.size) { EncodedLong(1, 1) }.apply {
        for (i in 1 until a.size) {
            set(i, get(i - 1) * P)
        }
    }

    constructor(x: IntArray) : this(prefixSumArray(x.size) { EncodedLong(x[it], x[it]) })
    constructor(x: String) : this(prefixSumArray(x.length) { EncodedLong(x[it].code, x[it].code) })

    inline fun hash(l: Int, r: Int) = (a[r] - a[l] * degs[r - l]).x

    companion object {
        private const val P1 = 239
        private const val P2 = 241
        private const val MOD1 = 1000000007
        private const val MOD2 = 1000000009
        private val P = EncodedLong(P1, P2)

        fun EncodedLongArray(n: Int, init: (Int) -> EncodedLong) = EncodedLongArray(LongArray(n) { init(it).x })
        private inline fun addMod(a: Int, b: Int, mod: Int): Int {
            val c = a + b
            return if (c >= mod) c - mod else c
        }

        private inline fun subMod(a: Int, b: Int, mod: Int): Int {
            val c = a - b
            return if (c < 0) c + mod else c
        }

        private inline fun prefixSumArray(size: Int, elem: (Int) -> EncodedLong) =
            EncodedLongArray(size + 1) { EncodedLong(0) }.apply {
                for (i in 0 until size) {
                    set(i + 1, get(i) * P + elem(i))
                }
            }
    }
}
