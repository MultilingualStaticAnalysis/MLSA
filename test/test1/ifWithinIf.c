int main(){
	int x = 5;
	int y = 1;
	if (x > 1)
	{
		y = x*y;
		x = x - 1;
		if (y < 4)
		{
			y = 4;
		}
		else
		{
			y = 3;	
		}	
	}
	else
	{
		x = 1;
	}
}
