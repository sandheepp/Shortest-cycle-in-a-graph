for(int i=0;i<V;i++)
{
    
}

void findloop(int dis[], src)
{
    int smallest = __INT_MAX__;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
           if(dis[i][j]==0)
           {
               dis[i][j] = __INT_MAX__;
           }
            if ((dis[i][j]+dis[j][i])< smallest)
            {
                smallest =dis[i][j]+dis[j][i] ;
            }
        }        
    }
    print("%d",smallest);
}