#include <fstream>
using namespace std;
template <class Type>
class Tree
{	private :
		struct Node
		{	Type data ;
			Node* son ;
			Node* brother ;
			
			Node( const Node* obj )
			{	son = brother = NULL ;
				data = NULL ;
				if( obj != NULL )
				{	data = obj->data ;
					if( obj->son != NULL )
						son = new Node( obj->son ) ;
					if( obj->brother != NULL )
						brother = new Node( obj->brother ) ;		
				}
				
			}
			Node(  ) : son( NULL ) , brother( NULL ) { }
			Node( Type item , Node* S = NULL , Node* B = NULL )
			{	data = item ;
				son = S ;
				brother = B ;
			}
			~Node( ) { } ;
		} ;
		Node* root ;
		int length( Node* t ) ;
		void preOrder( Node* ) ;
		void postOrder( Node* ) ;
	
	public	:
		Tree( )
		{	root = NULL ;	}
		Tree( const Node* p )
		{	if( p == NULL )
				root = NULL ;
			else
				root = new Node( p ) ;	
		}
		Tree( const Type& value ) 
		{	if( value != NULL )
				root = new Node( value ) ;
			else
				root = NULL ;
		}
		Tree( const Tree& obj )
		{	if( obj.root != NULL )
				root = new Node( obj.root ) ;
			else
				root = NULL ;
		}
		bool isEmpty( )
		{	return root == NULL ;	}
		int length( ) 
		{	return length( root ) ;	}
		Node* returnSon( )
		{	Node* tmp  = NULL ;
			if( root->son != NULL )
				tmp = root->son ;
			if( root->son != NULL )
				root->son = root->son->brother ;
			if( tmp != NULL )
				tmp->brother = NULL ;
			return tmp ;
		}
		Type getRootData( )
		{	return root->data ;	}
		void putSon( Tree* p )
		{	Node* n = root->son ;
			root->son = p->root ;
			root->son->brother = n ;				
		}

} ;
template<class Type>
int Tree<Type>::length( Node* t )
{	int  currentLength = 1 ;
	Node* p = t ;
	if( t->son == NULL )
		return 1 ;
	else
	{	p = t->son ;
		while( p != NULL )
		{	currentLength += length( p ) ;
			p = p->brother ;
		}
	}
	return currentLength ;
}
template<class Type>
class BernoulliQueue
{	private :
		Tree<Type>** root ; 
		int length ;
		int maxSize ;
		void doubleSpace( ) ;
	public :
		void insert(  int i , Tree<Type>* p ) 
		{	root[i] = p ;	
			length += pow( 2.0 , i/1.0 ) ;
			
		}
		Type deQueue( ) ;
		Type min();
		int returnArraySize( )
		{	int n = 0 ;
			for( int i = length ; i >0 ; i /= 2 )	
				n++ ;
		
			return n ;
		}
		int returnLength( )
		{	return length ;	}
		BernoulliQueue( )
		{	
			root = new Tree<Type>*[10]  ;
			for(  int i = 0 ; i < 10 ; i++ )
				root[i] = NULL ;
			length = 0 ;
			maxSize = 10 ;
		}
		BernoulliQueue( const Type& value )
		{	root = new Tree<Type>*[10]  ;
			length = 1 ;
			maxSize = 10 ;
			root[0] = new Tree<Type >( value ) ;
			for( int i = 1 ; i < maxSize ; i++ )
				root[i] = NULL ;
		}
		BernoulliQueue( const BernoulliQueue<Type>& obj )
		{	length = obj.length ;
			maxSize = obj.maxSize ;
			root = new Tree<Type>*[maxSize] ;
			for( int i = 0 ; i < maxSize ; i++ )
				if( obj.root[i] != NULL )
					root[i] = new Tree<Type>( *(obj.root[i]) ) ;
				else
					root[i] = NULL ;
			
		}
		BernoulliQueue<Type>& operator = (  const BernoulliQueue<Type>& obj   )
		{	length = obj.length ;
			maxSize = obj.maxSize ;
			root = new Tree<Type>*[maxSize] ;
			
			for( int i = 0 ; i < maxSize ; i++ )
				if( obj.root[i] != NULL )
					root[i] = new Tree<Type>( *(obj.root[i]) ) ;
				else
					root[i] = NULL ;
		
			return *this ;
		}
		void enQueue( Type x ) ;
		friend BernoulliQueue<Type> putTogether( BernoulliQueue<Type>& lobj , BernoulliQueue<Type>& robj ) 
		{	BernoulliQueue<Type> obj ;
			int j , k ;
			int i = 0 ;
			j = lobj.returnArraySize( ) ;
			k = robj.returnArraySize( ) ; 
			obj.length = lobj.returnLength( ) + robj.returnLength( ) ;

			while( j != 0 && k != 0 )
			{	if( i >= obj.maxSize )
					obj.doubleSpace( ) ;

				if( lobj.root[i] != NULL && robj.root[i] != NULL )
				{	Tree<Type>* p1 = new Tree<Type>( *( lobj.root[i] )) ;
					Tree<Type>* p2 = new Tree<Type>( *( robj.root[i] )) ;
					if( p1->getRootData( ) > p2->getRootData( ) )
					{	p2->putSon( p1 ) ;
						if( obj.root[i+1] == NULL )
							obj.root[i+1] = p2 ;
						else
						{	int n = i + 1 ;
							
							while(  obj.root[n] != NULL )
							{	if( n > obj.maxSize )
									obj.doubleSpace( ) ;
								Tree<Type>* p3 = new Tree<Type>(*(obj.root[n])) ;
								delete obj.root[n] ;
								obj.root[n] = NULL ;
								if( p3->getRootData( ) > p2->getRootData( ))
								{	p2->putSon( p3 ) ;
								}
								if( p3->getRootData( ) < p2->getRootData( ))
								{	p3->putSon( p2 ) ;
									p2 = p3 ;
								}
								n++ ;
							}
							obj.root[n] = p2 ;
						}
					}
					else
					{	p1->putSon( p2 ) ;
						if( obj.root[i+1] == NULL )
							obj.root[i+1] = p1 ;
						else
						{	int n = i + 1 ;
							
							while(  obj.root[n] != NULL )
							{	if( n > obj.maxSize )
									obj.doubleSpace( ) ;
								Tree<Type>* p3 = new Tree<Type>(*(obj.root[n])) ;
								delete obj.root[n] ;
								obj.root[n] = NULL ;
								if( p3->getRootData( ) > p1->getRootData( ))
								{	p1->putSon( p3 ) ;
								}
								if( p3->getRootData( ) < p1->getRootData( ))
								{	p3->putSon( p1 ) ;
									p1 = p3 ;
								}
								n++ ;
							}
							obj.root[n] = p1 ;
						}
					}
				}
				if( lobj.root[i] != NULL && robj.root[i] == NULL )
				{	Tree<Type>* p1 = new Tree<Type>( *( lobj.root[i] )) ;
					if( obj.root[i] == NULL )
						obj.root[i] = p1 ;
					else
					{	int n = i + 1 ;
						Tree<Type>* p2 = new Tree<Type>(*( obj.root[i] )) ;
						obj.root[i] = NULL ;
						if( p1->getRootData( ) < p2->getRootData( ))
							p1->putSon( p2 ) ;
						else
						{	p2->putSon( p1 ) ;
							p1 = p2 ;
						}
						while( obj.root[n] != NULL )
						{	if( n > obj.maxSize )
								obj.doubleSpace( ) ;
							p2 = new Tree<Type>(*( obj.root[n] )) ;
							delete obj.root[i] ;
							obj.root[i] = NULL ;
							if( p1->getRootData( ) < p2->getRootData( ))
							p1->putSon( p2 ) ;
							else
							{	p2->putSon( p1 ) ;
								p1 = p2 ;
							}
							n++ ;
						}
						obj.root[n] = p1 ;
					}
					
				}
				if( robj.root[i] != NULL && lobj.root[i] == NULL )
				{	Tree<Type>* p1 = new Tree<Type>( *( robj.root[i] )) ;
					if( obj.root[i] == NULL )
						obj.root[i] = p1 ;
					else
					{	int n = i + 1 ;
						Tree<Type>* p2 = new Tree<Type>(*( obj.root[i] )) ;
						if( p1->getRootData( ) < p2->getRootData( ))
							p1->putSon( p2 ) ;
						else
						{	p2->putSon( p1 ) ;
							p1 = p2 ;
						}
						while( obj.root[n] != NULL )
						{	if( n > obj.maxSize )
								obj.doubleSpace( ) ;
							p2 = new Tree<Type>(*( obj.root[n] )) ;
							if( p1->getRootData( ) < p2->getRootData( ))
							p1->putSon( p2 ) ;
							else
							{	p2->putSon( p1 ) ;
								p1 = p2 ;
							}
							n++ ;
						}
						obj.root[n] = p1 ;
					}
					
				}

				j-- ;		k-- ;	 i++ ;	
			}			
			while( j != 0 )
			{	if( lobj.root[i] != NULL )
				{		Tree<Type>* p1 = new Tree<Type>( *( lobj.root[i] )) ;
						if( obj.root[i] == NULL )
							obj.root[i] = p1 ;
						else
						{	int n = i + 1 ;
							Tree<Type>* p2 = new Tree<Type>(*( obj.root[i] )) ;
							delete obj.root[i] ;
							obj.root[i] = NULL ;
							if( p1->getRootData( ) < p2->getRootData( ))
								p1->putSon( p2 ) ;
							else
							{	p2->putSon( p1 ) ;
								p1 = p2 ;
							}
							while( obj.root[n] != NULL )
							{	if( n > obj.maxSize )
									obj.doubleSpace( ) ;
								p2 = new Tree<Type>(*( obj.root[n] )) ;
								obj.root[n] ;
								obj.root[n] = NULL ;
								if( p1->getRootData( ) < p2->getRootData( ))
								p1->putSon( p2 ) ;
								else
								{	p2->putSon( p1 ) ;
									p1 = p2 ;
								}
								n++ ;
							}
							obj.root[n] = p1 ;
						}	
				}
						j-- ;	i++ ;
			}
			while( k != 0 )
			{	if( robj.root[i] != NULL )
				{	Tree<Type>* p1 = new Tree<Type>( *( robj.root[i] )) ;
					if( obj.root[i] == NULL )
						obj.root[i] = p1 ;
					else
					{	int n = i + 1 ;
						Tree<Type>* p2 = new Tree<Type>(*( obj.root[i] )) ;
						obj.root[i] ;
						obj.root[i] = NULL ;
						if( p1->getRootData( ) < p2->getRootData( ))
							p1->putSon( p2 ) ;
						else
						{	p2->putSon( p1 ) ;
							p1 = p2 ;
						}
						while( obj.root[n] != NULL )
						{	if( n > obj.maxSize )
								obj.doubleSpace( ) ;
							p2 = new Tree<Type>(*( obj.root[n] )) ;
							obj.root[n] ;
							obj.root[n] = NULL ;
							if( p1->getRootData( ) < p2->getRootData( ))
							p1->putSon( p2 ) ;
							else
							{	p2->putSon( p1 ) ;
								p1 = p2 ;
							}
							n++ ;
						}
						obj.root[n] = p1 ;
					}
				}
					k-- ;		i++ ;
			}
			return obj ;
		}
} ;
template<class Type>
Type BernoulliQueue<Type>::min( )
{	int i = 0 ;
	Type min  ;
	for(  i = 0 ; i < length ; i++ )
		if( root[i] != NULL )
		{	min	= root[i]->getRootData( ) ;
			break ;
		}
	for( ; i < length ; i++ )
		if( root[i] != NULL && root[i]->getRootData( ) < min  )
			min	= root[i]->getRootData( ) ;
	return min;
}
template<class Type>
Type BernoulliQueue<Type>::deQueue( )
{	int i = 0 ;
	int j = 0 ;
	Type min  ;
	for(  i = 0 ; i < length ; i++ )
		if( root[i] != NULL )
		{	min	= root[i]->getRootData( ) ;
			j = i ;
			break ;
		}
	for( ; i < length ; i++ )
		if( root[i] != NULL && root[i]->getRootData( ) < min  )
		{	min	= root[i]->getRootData( ) ;
			j = i ;
		}
	Tree<Type>* p = root[j] ;
	length = length - p->length( ) ;	
	root[j] = NULL ;
	BernoulliQueue<Type> obj ;
	Tree<Type> *pt = new Tree<Type>( p->returnSon( )) ;
	while( !pt->isEmpty( ))
	{	int n = -1 ;
		for( int l = pt->length( )  ; l > 0 ; l /= 2 )
			n++ ;
		obj.insert( n, pt ) ;
		pt = new Tree<Type>( p->returnSon( )) ;
	}
	
	
	BernoulliQueue<Type> result ;
	result = putTogether( (*this) , obj ) ;
	(*this) = result ;		
	return min ;
}
template<class Type>
void BernoulliQueue<Type>::enQueue( Type x )
{	BernoulliQueue<Type> obj( x ) ;
	BernoulliQueue<Type> result ;
	result = putTogether( (*this) , obj ) ;
	(*this) = result ;		
}
template<class Type>
void BernoulliQueue<Type>::doubleSpace( )
{	int newMaxSize = maxSize * 2 ;
	Tree<Type>** p = root ;
	root = new Tree<Type>*[newMaxSize] ;	
	
	for( int i = 0 ; i < maxSize ; i++ )
		root[i] = new Tree<Type>( *(p[i])) ; 	
	for( int i = maxSize ; i < newMaxSize ; i++ )
		root[i] = NULL ;
	maxSize = newMaxSize ;
	
	delete p ;
}
int main(){
	ofstream fout("Bernouli.out");
	ifstream fin("Bernouli.in");
	BernoulliQueue<int> a;
	int n,para;
	char opt[10];
	fin>>n;
	for(int i=0;i<n;i++){
		fin>>opt;
		if (opt[0]=='i'){
			fin>>para;
			a.enQueue(para);
		}
		else if (opt[0]== 'd' )
			a.deQueue();
		else if (opt[0] == 'm'){
			fout<<a.min()<<endl;
		}
	}
	fout.close();
	fin.close();
	return 0 ;
}