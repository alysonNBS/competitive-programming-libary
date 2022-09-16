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

// time-complexity: O(n log n)
// space-complexity: O(n)
class SegtreeToLIS {
    int size; // size is the 1st 2-pow greater or equal n
    vector<pair<int, int>> tree;

public:
    SegtreeToLIS(int n) {
        size = 1;
        while (size < n)
            size <<= 1;
        tree.assign(size << 1, {0, 0});
        this->update(0, {0, 1});
    }

    void update(int index, pair<int, int> value) {
        return update(index, value, 0, 0, size);
    }

    void update(int index, pair<int, int> value, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (value.first != tree[x].first) tree[x] = value;
            else tree[x] = {tree[x].first, tree[x].second + value.second};
            return;
        }
        int mid = (lx + rx) >> 1;
        if (index < mid) update(index, value, (x << 1) + 1, lx, mid);
        else update(index, value, (x << 1) + 2, mid, rx);
        
        if (tree[(x << 1) + 1].first > tree[(x << 1) + 2].first) tree[x] = tree[(x << 1) + 1];
        else if (tree[(x << 1) + 1].first < tree[(x << 1) + 2].first) tree[x] = tree[(x << 1) + 2];
        else tree[x] = {tree[(x << 1) + 1].first, tree[(x << 1) + 1].second + tree[(x << 1) + 2].second};
    }

    pair<int, int> find(int index) {
        return find(index, 0, 0, size);
    }

    pair<int, int> find(int index, int x, int lx, int rx) {
        if (lx >= index) return {0, 0};
        if (rx <= index) return tree[x];
        int mid = (lx + rx) >> 1;
        auto left = find(index, (x << 1) + 1, lx, mid);
        auto right = find(index, (x << 1) + 2, mid, rx);

        if (left.first > right.first) return left;
        else if (right.first > left.first) return right;
        else return {left.first, left.second + right.second};
    }
};

int findNumberOfLIS(vector<int>& nums) {
    int n = nums.size();
    SegtreeToLIS segtree(n + 1);
    //compress numbers from 1 to n
    {
        map<int,list<int>> mp;
        for (int i = 0; i < n; ++i) {
            if (mp.find(nums[i]) == mp.end())
                mp[nums[i]] = list<int>();
            mp[nums[i]].push_back(i);
        }
        int compress_num = 1;
        for (const auto& pair: mp) {
            for (const auto& index : pair.second)
                nums[index] = compress_num;
            ++compress_num;
        }
    }
    
    for (const auto& num : nums) {
        auto element = segtree.find(num);
        segtree.update(num, {element.first + 1, element.second});
    }

    return segtree.find(n + 1).second;
}
