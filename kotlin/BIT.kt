private class BIT(val n: Int) {
    private val x = $TYPE$Array(n)

    fun add(pos:Int, value: $TYPE$) {
        var ppos = pos
        while (ppos < n) {
            x[ppos] += value
            ppos = ppos or (ppos + 1)
        }
    }

    fun get(pos: Int): $TYPE$ {
        var ans: $TYPE$ = 0
        var ppos = pos
        while (ppos != -1) {
            ans += x[ppos]
            ppos = (ppos and (ppos + 1)) - 1
        }
        return ans
    }
    fun get(l:Int, r:Int) = get(r - 1) - get(l - 1)
}
