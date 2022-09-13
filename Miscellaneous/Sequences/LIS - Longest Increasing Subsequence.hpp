// time-complexity: O(n log n)
// space-complexity: O(n)
int lengthOfLIS(vector<int>& nums) {
    const int INF = 0x3f3f3f3f;
    vector<int> dp(nums.size() + 1, INF);
    int length = 0;
    dp[0] = -INF;
    for (const auto& num : nums) {
        // change lower_bound to upper_bound if u want non-decreasing instead of it
        int i = lower_bound(dp.begin(), dp.end(), num) - dp.begin();
        dp[i] = min(dp[i], num);
        length = max(length, i);
    }
    return length;
}

// time-complexity: O(n^2)
// space-complexity: O(n)
int findNumberOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(2, vector<int>(n, 1));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < i; ++j)
            if (nums[i] > nums[j])
                dp[0][i] = max(dp[0][i], dp[0][j] + 1);
    
    int lengthOfLIS = *max_element(dp[0].begin(), dp[0].end());
    int answer {0};
    
    for (int i = 0; i < n; ++i)
        if (dp[0][i] != 1)
            dp[1][i] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[0][i] == dp[0][j] + 1 && nums[i] > nums[j])
                dp[1][i] += dp[1][j];
        }
        if (dp[0][i] == lengthOfLIS)
            answer += dp[1][i];
    }
    
    return answer;
}
