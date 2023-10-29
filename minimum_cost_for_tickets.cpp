//Minimum cost for Tickets Part 1:


int solve(int n, vector<int>& days, vector<int>& cost, int index) {
	
	//Base Case
	if(index >= n) {
		return 0;
	}
	
	//1 day pass
	int option1 = cot[0] + solve(n, days, cost, index+1);
	
	int i;
	//7 days pass
	for(i = index; i<n && days[i] < days[index] + 7; i++);
	
	int option2 = cost[1] + solve(n,days, cost, i);
	
		//30 days pass
	for(int j = index; j<n && days[j] < days[index] + 30; j++);
	
	int option3 = cost[2] + solve(n,days, cost, j);
	
	return min(option1, min(option2, option3));

}

int minimumCoins(int n, vector<int> days, vector<int> cost) {
	return solve(n, days, cost, 0);
}

//Using Memoization...

int solveMem(int n, vector<int>& days, vector<int>& cost, int index, vector<int>& dp) {
	
	//Base Case
	if(index >= n) {
		return 0;
	}
	
	if(dp[index] != -1)
	return dp[index];
	
	//1 day pass
	int option1 = cost[0] + solveMem(n, days, cost, index+1, dp);
	
	int i;
	//7 days pass
	for(i = index; i<n && days[i] < days[index] + 7; i++);
	
	int option2 = cost[1] + solveMem(n,days, cost, i, dp);
	
	//30 days pass
	for(int j = index; j<n && days[j] < days[index] + 30; j++);
	
	int option3 = cost[2] + solveMem(n,days, cost, j, dp);
	
	dp[index] =  min(option1, min(option2, option3));
    return dp[index];
}

int minimumCoins(int n, vector<int> days, vector<int> cost) {
	vector<int> &dp(n+1,-1);
	
	return solveMem(n, days, cost, 0, dp);
}



//Using Tabulation...

int solveTab(int n, vector<int>& days, vector<int>& cost) {
	
	vector<int> dp(n+1, INT_MAX);
	dp[n] = 0;
	
	for(k = n-1; k>=0; k--) {
	
	//1 day pass
	int option1 = cost[0] + dp[k+1];
	
	int i;
	//7 days pass
	for(i = k; i<n && days[i] < days[k] + 7; i++);
	
	int option2 = cost[1] + dp[i];
	
		//30 days pass
	for(int j = k; j<n && days[j] < days[k] + 30; j++);
	
	int option3 = cost[2] + dp[j];
	
	dp[k] =  min(option1, min(option2, option3));
    
}
return dp[0];
}


int minimumCoins(int n, vector<int> days, vector<int> cost) {
	return solve(n, days, cost);
}

//.................Very IMP and Thought Provoking.................
//Optimized Space Complexity...
//T.C: O(n)
//S.C: O(1)

int minimumCoins(int n, vector<int> days, vector<int> cost) {
	int ans = 0;
	
	queue<pair<int, int >> month;
	queue<pair<int, int >> week;
	
	for(int day: days) {
		
		//step 1: Remove expired days...
		while(!month.empty() && month.front().first + 30 <= day)
		month.pop();
		
		while(!week.empty() && week.front().first + 7 <= day)
		week.pop();
		
		//step2: add cost for current day
		week.push(make_pair(day, ans+cost[1]));
		month.push(make_pair(day, ans+cost[2]));
		
		//step3: Ans Update...
		ans = min(ans+cost[0], min(week.front().second, month.front().second));
	}
	return ans;
}
