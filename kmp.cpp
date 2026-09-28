vector<int> kmp(const string &s) {
    int n = (int)s.size();
    vector<int> dp(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j])
            j = dp[j - 1];
        if (s[i] == s[j])
            j++;
        dp[i] = j;
    }
    return dp;
}
// start indices of all (possibly overlapping) occurrences of pat in text, O(|text| + |pat|)
vector<int> kmp_match(const string &text, const string &pat) {
    vector<int> res;
    if (pat.empty())
        return res;
    auto f = kmp(pat);
    int m = (int)pat.size();
    for (int i = 0, j = 0; i < (int)text.size(); i++) {
        while (j && text[i] != pat[j])
            j = f[j - 1];
        if (text[i] == pat[j])
            j++;
        if (j == m) {
            res.push_back(i - m + 1);
            j = f[j - 1];
        }
    }
    return res;
}
/************** KMP algorithm *************/
