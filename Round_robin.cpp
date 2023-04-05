#include <bits/stdc++.h>
using namespace std;
struct processes
{
    int id, b, a, w, tat, et, pr;
};
struct ready_queue
{
    int bt, id, a, pr;
};
struct gantt_chart
{
    int id, s, e;
};
bool comparewth(const struct processes &x, const struct processes &y)
{
    return x.a < y.a;
}
struct ready_queue make_obj(struct processes ar)
{
    struct ready_queue m;
    m.a = ar.a;
    m.bt = ar.b;
    m.id = ar.id;
    m.pr = ar.pr;
    return m;
}
void RR(vector<struct processes> ar, int q)
{
    vector<struct gantt_chart> g;
    vector<struct ready_queue> rq;
    int i = 0, t = 0;
    rq.push_back(make_obj(ar[i++]));
    while (rq.size() != 0)
    {
        if (g.size() == 0)
            t = rq[0].a;
        else if (g[g.size() - 1].e < rq[0].a)
            t = rq[0].a;
        else
            t = g[g.size() - 1].e;
        struct gantt_chart M;
        M.s = t;
        M.id = rq[0].id;
        if (rq[0].bt - q <= 0)
        {
            t += rq[0].bt;
            rq.erase(rq.begin());
        }
        else
        {
            rq[0].bt -= q;
            t += q;
            for (; i < ar.size(); i++)
            {
                if (ar[i].a <= t)
                    rq.push_back(make_obj(ar[i]));
                else
                    break;
            }
            struct ready_queue x = rq[0];
            rq.erase(rq.begin());
            rq.push_back(x);
        }
        M.e = t;
        g.push_back(M);
    }
    for (int i = 0; i < g.size(); i++)
        cout << g[i].id << " " << g[i].s << " " << g[i].e << endl;
    float Atat = 0, Awt = 0;
    for (int i = 0; i < ar.size(); i++)
    {
        for (int j = 0; j < g.size(); j++)
        {
            if (ar[i].id == g[j].id)
                ar[i].et = g[j].e;
        }
        ar[i].tat = ar[i].et - ar[i].a;
        ar[i].w = ar[i].tat - ar[i].b;
        Atat += ar[i].tat;
        Awt += ar[i].w;
    }
    cout << "+\t\tAt\t\tBt\t\tPr\t\tTAT\t\tWt\t\tEt" << endl;
    for (int i = 0; i < ar.size(); i++)
        cout << "p" << ar[i].id << "\t\t" << ar[i].a << "\t\t" << ar[i].b << "\t\t" << ar[i].pr << "\t\t" << ar[i].tat << "\t\t" << ar[i].w << "\t\t" << ar[i].et << endl;
    cout << "Average Turn Around Time : " << Atat / ar.size() << endl;
    cout << "Average Waiting Time : " << Awt / ar.size() << endl;
}
int main()
{
    int n, q;
    cout << "Enter number of preocessess : ";
    cin >> n;
    cout << "Enter Time Quantum : ";
    cin >> q;
    if (n == 0)
        return 0;
    vector<struct processes> ar(n);
    for (int i = 0; i < n; i++)
    {
        ar[i].id = i + 1;
        cout << "Enter Arrival tome of p" << (i + 1) << " : ";
        cin >> ar[i].a;
        cout << "Enter burst times of p" << (i + 1) << " : ";
        cin >> ar[i].b;
    }
    sort(ar.begin(), ar.end(), comparewth);
    RR(ar, q);
    return 0;
}