#include <bits/stdc++.h>
using namespace std;
struct processes
{
    int id, b, a, w, tat, et, pr;
};
bool comparewth(const struct processes &x, const struct processes &y)
{
    return x.a < y.a;
}
struct ready_queue
{
    int bt, id, a, pr;
};
struct gantt_chart
{
    int id, s, e;
};
bool comparewthp(const struct ready_queue &x, const struct ready_queue &y)
{
    if (x.pr == y.pr)
    {
        if (x.a == y.a)
        {
            return x.id < y.id;
        }
        else
            return x.a < y.a;
    }
    else
        return x.pr > y.pr;
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
void priority_preempted(vector<struct processes> ar, int n)
{
    vector<struct gantt_chart> g;
    vector<struct ready_queue> rq;
    int i = 0, t = 0;
    rq.push_back(make_obj(ar[i++]));
    while (rq.size() != 0)
    {
        int x = 0;
        if (g.size() == 0)
            t = rq[0].a;
        else if (g[g.size() - 1].e < rq[0].a)
            t = rq[0].a;
        else
            t = g[g.size() - 1].e;
        struct gantt_chart M;
        M.s = t;
        M.id = rq[0].id;
        while (1)
        {
            t++;
            --rq[0].bt;
            if (rq[0].bt == 0)
            {
                rq.erase(rq.begin());
                x = 1;
            }
            for (; i < n; i++)
            {
                if (ar[i].a <= t)
                {
                    rq.push_back(make_obj(ar[i]));
                    sort(rq.begin(), rq.end(), comparewthp);
                    if (ar[i].id == rq[0].id)
                        x = 1;
                }
                else
                    break;
            }
            if (x == 1)
                break;
        }
        if (i < n && rq.size() == 0)
        {
            rq.push_back(make_obj(ar[i++]));
            for (; i < n; i++)
            {
                if (rq[0].a == ar[i].a)
                    rq.push_back(make_obj(ar[i]));
                else
                    break;
            }
            sort(rq.begin(), rq.end(), comparewthp);
        }
        M.e = t;
        g.push_back(M);
    }
    for (int i = 0; i < g.size(); i++)
        cout << g[i].id << " " << g[i].s << " " << g[i].e << endl;
    float Atat = 0, Awt = 0;
    for (int i = 0; i < n; i++)
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
    for (int i = 0; i < n; i++)
        cout << "p" << ar[i].id << "\t\t" << ar[i].a << "\t\t" << ar[i].b << "\t\t" << ar[i].pr << "\t\t" << ar[i].tat << "\t\t" << ar[i].w << "\t\t" << ar[i].et << endl;
    cout << "Average Turn Around Time : " << Atat / n << endl;
    cout << "Average Waiting Time : " << Awt / n << endl;
}
int main()
{
    int n;
    cout << "Enter number of preocessess : ";
    cin >> n;
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
        cout << "Enter priority of p" << (i + 1) << " : ";
        cin >> ar[i].pr;
    }
    sort(ar.begin(), ar.end(), comparewth);
    priority_preempted(ar, n);
    return 0;
}