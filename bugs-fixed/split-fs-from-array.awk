BEGIN {
        a[1] = "elephantine"
        a[2] = "e"
        print split(a[1],a,a[2]), a[2], a[3], split(a[2],a,a[2])
}
