#include "CombinatoricNum.h"
#include <vector>

using namespace std;

uint32_t placement(const uint32_t& m, const uint32_t& n)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return m;

	int res = 1;
	for (size_t i = 0; i < n; i++)
	{
		if (res <= UINT32_MAX / m)
		{
			res *= m;
		}
		else
		{
			throw string("ERROR: the number could not be computed due to overflow");
		}
	}

	return res;
}

uint32_t placementWthoutRep(const uint32_t& m, const uint32_t& n)
{
	if (n == 0)
		return 1;
	if (n == 1)
		return m;
	if (n > m)
		return 0;

	uint32_t res = 1;

	for (size_t i = m; i > m - n; i--)
	{
		if (res <= UINT32_MAX / i)
		{
			res *= i;
		}
		else
		{
			throw string("ERROR: the number could not be computed due to overflow");
		}
	}

	return res;
}

uint32_t permutations(const uint32_t& n)
{
	if (n == 0)
		return 1;

	uint32_t res = 1;

	for (size_t i = 1; i <= n; i++)
	{
		if (res <= UINT32_MAX / i)
		{
			res *= i;
		}
		else
		{
			throw string("ERROR: the number could not be computed due to overflow");
		}
	}

	return res;
}

uint32_t combinations(uint32_t m, uint32_t n)
{
	if (n > m)
		return 0;
	if (n == m || n == 0)
		return 1;
	if (n == 1 || m == n + 1)
		return m;
	if (n > m - n)
		n = m - n;

	uint32_t res = m - n + 1;
	uint32_t k = m - n + 2;

	for (int i = 2; i <= n; i++)
	{
		if (res / i <= (UINT32_MAX - (res % i) * (k / i)) / k)
		{
			res = (res / i) * k + (res % i) * (k / i);
			k = k + 1;
		}
		else
		{
			throw string("ERROR: the number could not be computed due to overflow");
		}
	}

	return res;
}

uint32_t stirling(const uint32_t& m, const uint32_t& n)
{
	if (m == n || n == 1)
		return 1;
	if (n == 0 || n > m)
		return 0;
	
	vector<uint32_t> d;
	uint32_t k = min(n, m - n + 1);
	uint32_t s = max(n, m - n + 1);

	for (size_t i = 0; i <= k; i++)
	{
		d.push_back(1);
	}

	for (size_t i = 2; i <= s; i++)
	{
		for (size_t j = 2; j <= k; j++)
		{
			if (k == n)
			{
				if (d[j] <= (UINT32_MAX - d[j - 1]) / j)
				{
					d[j] = d[j - 1] + j * d[j];
				}
				else
				{
					throw string("ERROR: the number could not be computed due to overflow");
				}
			}
			else
			{
				if (d[j] <= (UINT32_MAX - d[j - 1]) / i)
				{
					d[j] = d[j - 1] + i * d[j];
				}
				else
				{
					throw string("ERROR: the number could not be computed due to overflow");
				}
			}
		}
	}

	return d[k];
}

uint32_t bell(const uint32_t& m)
{
	if (m == 0)
		return 1;

	vector<uint32_t> a;
	for (uint32_t i = 0; i <= m; i++)
	{
		a.push_back(1);
	}
	uint32_t t, s;
	for (size_t i = 2; i <= m; i++)
	{
		t = a[1];
		a[1] = a[i - 1];
		for (size_t j = 2; j <= i; j++)
		{
			s = a[j];
			if (a[j - 1] <= UINT32_MAX - t)
			{
				a[j] = a[j - 1] + t;
			}
			else
			{
				throw string("ERROR: the number could not be computed due to overflow");
			}
			t = s;
		}
	}

	return a[m];
}