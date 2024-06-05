//Slopes are INCREASING -> query for MAXIMUM
//Slopes are DECREASING -> query for MINIMUM
struct Line {
    mutable long long m, b, p;
    bool operator<(const Line &o) const { return m < o.m; }
    bool operator<(const long long x) const { return p < x; }
};
 
struct MonotonicCHT : deque<Line> {
    const long long inf = long longONG_MAX;
    long long div(long long a, long long b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(Line &x, Line &y) {
        x.p = div(y.b - x.b, x.m - y.m);
        return x.p >= y.p;
    }
    void add(long long m, long long b) {
        Line l = {m, b, inf};
        if(!empty()) isect(at(size() - 1), l);
        while(size() >= 2 && isect(at(size() - 2), at(size() - 1))) {
            pop_back();
            isect(at(size() - 1), l);
        }
        push_back(l);
    }
    long long query(long long x) {
        assert(!empty());
        while(x > front().p) {
            pop_front();
        }
        auto l = front();
        return l.m * x + l.b;
    }
};
