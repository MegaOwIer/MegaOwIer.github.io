vector<LL> fRC;
factorize(RC, fRC);

vector<LL> conv(fRC.size());
for(size_t i = 0; i < fRC.size() && fRC[i] <= K; i++) {
    if(cycle_length.count(fRC[i])) {
        conv[i] = cycle_length[fRC[i]];
    }
}
for(int pr : primes) if(RC % pr == 0) {
    for(size_t i = 0; i < fRC.size(); i++) {
        if(fRC[i] % pr != 0) {
            continue;
        }
        size_t idx = lower_bound(fRC.begin(), fRC.end(), fRC[i] / pr) - fRC.begin();
        conv[i] += conv[idx];
    }
}

function<LL(int, int)> calc = [&] (int i, int j) {
    LL lcm = (LL)i / __gcd(i, j) * j;
    size_t idx = lower_bound(fRC.begin(), fRC.end(), lcm) - fRC.begin();
    return Pow(conv[idx], (LL)r * c / lcm) * phi[i] % mod * phi[j] % mod;
};
