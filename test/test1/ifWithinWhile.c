int main(){
	int x = 5;
	int y = 1;
	while (x > 1)
	{
		y = x*y;
		x = x - 1;
		if (x > 3)
		{
			x = 3;
		}
		else
		{
			x = 2;
		}	
	}
}
