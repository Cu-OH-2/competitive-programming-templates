// 浮点数三分
ld tes(ld lef, ld rig)
{
    if (fabs(lef - rig) < 1e-7) return lef;
    ld midl = lef + (rig - lef) / 3;
    ld midr = rig - (rig - lef) / 3;
    ld resl = check(midl), resr = check(midr);
    if (resl > resr) return tes(lef, midr);
    else return tes(midl, rig);
}

// 整数三分 [l,r]
ll tes(ll lef, ll rig)
{
    if (lef == rig) return lef;
    ll midl = lef + (rig - lef) / 3;
    ll midr = rig - (rig - lef) / 3;
    ll resl = check(midl), resr = check(midr);
    if (resl >= resr) return tes(lef, midr - 1);
    else return tes(midl + 1, rig);
}