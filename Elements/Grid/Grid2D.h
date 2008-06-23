// - ------------------------------------------------------------------------------------------ - //
// Grid2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Grid_Grid2D_H__
#define __Grid_Grid2D_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Math Functions, Insert (creating rows and columns to fit, X/YAxis Only)
// - ------------------------------------------------------------------------------------------ - //
template< class tType = int >
class Grid2D {
	// - -------------------------------------------------------------------------------------- - //
	// Dimensions //
	size_t w, h;
	
	// Data Array //
	tType* Data;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline Grid2D() :
		w( 0 ),
		h( 0 ),
		Data( 0 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Grid2D( const size_t _w, const size_t _h, const tType& Type = tType() ) :
		w( _w ),
		h( _h ),
		Data( new tType[w*h] )
	{
		FillData(Type);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Grid2D( const Grid2D<tType>& Copy ) :
		w( Copy.w ),
		h( Copy.h ),
		Data( new tType[w*h] )
	{
		for ( size_t idx = w*h; idx--; ) {
			Data[ idx ] = Copy.Data[ idx ];
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Grid2D<tType>& operator = (const Grid2D<tType>& Copy) {
		if ( this != &Copy ) {
			if ( Data )
				delete [] Data;
			
			w = Copy.w;
			h = Copy.h;
			
			Data = new tType[ w*h ];
			for ( size_t idx = w*h; idx--; ) {
				Data[ idx ] = Copy.Data[ idx ];
			}
		}
		
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline ~Grid2D() {
		if ( Data )
			delete [] Data;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const size_t Width() const {
		return w;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t Height() const {
		return h;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t Size() const {
		return w * h;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline void FillData( tType* Dest, const size_t Size, const tType& Value = tType() ) {
		for ( size_t idx = Size; idx--; ) {
			Dest[ idx ] = Value;
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void FillData( const tType& Value = tType() ) {
		FillData( Data, Size(), Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetData( tType* NewData ) {
		if ( Data )
			delete [] Data;
			
		Data = NewData;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Index Generating functions.  Return a valid index for [] operator. //
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t Index( const size_t _x, const size_t _y ) const {
		// TODO: Assert out of bounds 
		return _x + (_y * w);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t IndexWrap( const size_t _x, const size_t _y ) const {
		return (_x % w) + ((_y % h) * w);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const size_t IndexNextWrap( const size_t _x, const size_t _y ) const {
		return (_x + (_y * w)) % Size();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const size_t IndexClip( int _x, int _y ) const {
		if ( _x >= w )
			_x = w - 1;
		else if ( _x < 0 )
			_x = 0;
			
		if ( _y >= h )
			_y = h - 1;
		else if ( _y < 0 )
			_y = 0;
			
		return Index( _x, _y );
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline tType& operator () ( const size_t _x, const size_t _y ) {
		return Data[ Index( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const tType& operator () ( const size_t _x, const size_t _y ) const {
		return Data[ Index( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline tType& operator [] ( const size_t _Index ) {
		// TODO: Assert out of bounds 
		return Data[ _Index ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const tType& operator [] ( const size_t _Index ) const {
		// TODO: Assert out of bounds 
		return Data[ _Index ];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline tType& Wrap( const size_t _x, const size_t _y ) {
		return Data[ IndexWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline const tType& Wrap( const size_t _x, const size_t _y ) const {
		return Data[ IndexWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with next line/first line wrapping //
	inline tType& NextWrap( const size_t _x, const size_t _y ) {
		return Data[ IndexNextWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with next line/first line wrapping //
	inline const tType& NextWrap( const size_t _x, const size_t _y ) const {
		return Data[ IndexNextWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline tType& Clip( int _x, int _y ) {
		return Data[ IndexClip( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const tType& Clip( const size_t _x, const size_t _y ) const {	
		return Data[ IndexClip( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get the position, returning the dead value if over //
	inline const tType& DeadClip( const size_t _x, const size_t _y, const tType& DeadValue = tType() ) const {
		if ( _x >= w )
			return DeadValue;
		else if ( _x < 0 )
			return DeadValue;
			
		if ( _y >= h )
			return DeadValue;
		else if ( _y < 0 )
			return DeadValue;
			
		return Data[ Index( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	
private:
	// - -------------------------------------------------------------------------------------- - //
	static inline tType* CopyData(
		const Grid2D< tType >& Src,
		const size_t NewWidth,
		const size_t NewHeight,
		const int SrcStartX,
		const int SrcStartY,
		const int DestStartX,
		const int DestStartY,
		const tType& InitValue = tType()
		)
	{
		tType* DataCopy = new tType[ NewWidth * NewHeight ];
		FillData( DataCopy, NewWidth * NewHeight, InitValue );
		
		size_t CopyWidth = 0;
		size_t CopyHeight = 0;
		
		// How much to Copy Wide //
		if ( NewWidth > Src.Width() ) {
			CopyWidth = Src.Width();
		}
		else {
			CopyWidth = NewWidth;
		}
		
		// How much to Copy Tall //
		if ( NewHeight > Src.Height() ) {
			CopyHeight = Src.Height();
		}
		else {
			CopyHeight = NewHeight;
		}
		
		// Copy Data //
		for ( size_t _y = CopyHeight; _y--; ) {
			for ( size_t _x = CopyWidth; _x--; ) {
				DataCopy[DestStartX + _x + ((DestStartY + _y) * NewWidth)] = 
					Src.Data[SrcStartX + _x + ((SrcStartY + _y) * Src.Width())];
			}
		}
		
		return DataCopy;
	}	
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D< tType > Copy(
		const Grid2D< tType >& Src,
		const size_t NewWidth,
		const size_t NewHeight,
		const int SrcStartX,
		const int SrcStartY,
		const int DestStartX,
		const int DestStartY,
		const tType& InitValue = tType()
		)
	{
		Grid2D< tType > NewGrid;
		
		NewGrid.SetData( CopyData( Src, NewWidth, NewHeight, SrcStartX, SrcStartY, DestStartX, DestStartY, InitValue ) );
		NewGrid.w = NewWidth;
		NewGrid.h = NewHeight;
		
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	static inline const Grid2D< tType > Merge(
		const Grid2D< tType >& GridA,
		const Grid2D< tType >& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& InitValue = tType()
		)
	{
		// Top corner of the grid //
		int GridX1 = GridAX;
		int GridY1 = GridAY;
		
		if ( GridX1 > GridBX )
			GridX1 = GridBX;
		if ( GridY1 > GridBY )
			GridY1 = GridBY;

			
		// Bottom corner of the grid //
		int GridX2 = GridAX + GridA.Width();
		int GridY2 = GridAY + GridA.Height();
		
		if ( GridX2 < (int)(GridBX + GridB.Width()) )
			GridX2 = GridBX + GridB.Width();
		if ( GridY2 < (int)(GridBY + GridB.Height()) )
			GridY2 = GridBY + GridB.Height();

		
		// Calculate the dimensions //
		int Width = GridX2 - GridX1;
		int Height = GridY2 - GridY1;

		
		// Calculate Start Positions //
		int AX = GridAX - GridX1;
		int AY = GridAY - GridY1;
		int BX = GridBX - GridX1;
		int BY = GridBY - GridY1;
			
		// Create a Grid to hold our copy //
		Grid2D< tType > NewGrid( Width, Height, InitValue );

		// Copy GridA //
		for ( size_t _y = GridA.Height(); _y--; ) {
			for ( size_t _x = GridA.Width(); _x--; ) {
				NewGrid( AX + _x, AY + _y ) = GridA( _x, _y );
			}
		}

		// Copy GridB //
		for ( size_t _y = GridB.Height(); _y--; ) {
			for ( size_t _x = GridB.Width(); _x--; ) {
				NewGrid( BX + _x, BY + _y ) = GridB( _x, _y );
			}
		}
		
		// Return the grid //
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D< tType > MergeBlend(
		const Grid2D< tType >& GridA,
		const Grid2D< tType >& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& TestValue = tType(),
		const tType& InitValue = tType()
		)
	{
		// Top corner of the grid //
		int GridX1 = GridAX;
		int GridY1 = GridAY;
		
		if ( GridX1 > GridBX )
			GridX1 = GridBX;
		if ( GridY1 > GridBY )
			GridY1 = GridBY;

			
		// Bottom corner of the grid //
		int GridX2 = GridAX + GridA.Width();
		int GridY2 = GridAY + GridA.Height();
		
		if ( GridX2 < (int)(GridBX + GridB.Width()) )
			GridX2 = GridBX + GridB.Width();
		if ( GridY2 < (int)(GridBY + GridB.Height()) )
			GridY2 = GridBY + GridB.Height();

		
		// Calculate the dimensions //
		int Width = GridX2 - GridX1;
		int Height = GridY2 - GridY1;

		
		// Calculate Start Positions //
		int AX = GridAX - GridX1;
		int AY = GridAY - GridY1;
		int BX = GridBX - GridX1;
		int BY = GridBY - GridY1;
			
		// Create a Grid to hold our copy //
		Grid2D< tType > NewGrid( Width, Height, InitValue );

		// Copy GridA //
		for ( size_t _y = GridA.Height(); _y--; ) {
			for ( size_t _x = GridA.Width(); _x--; ) {
				if ( GridA( _x, _y ) != TestValue )
					NewGrid( AX + _x, AY + _y ) = GridA( _x, _y );
			}
		}

		// Copy GridB //
		for ( size_t _y = GridB.Height(); _y--; ) {
			for ( size_t _x = GridB.Width(); _x--; ) {
				if ( GridB( _x, _y ) != TestValue )
					NewGrid( BX + _x, BY + _y ) = GridB( _x, _y );
			}
		}
		
		// Return the grid //
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D< tType > MergeBlendOnly(
		const Grid2D< tType >& GridA,
		const Grid2D< tType >& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& TestValue = tType(),
		const tType& InitValue = tType()
		)
	{
		// Top corner of the grid //
		int GridX1 = GridAX;
		int GridY1 = GridAY;
		
		if ( GridX1 > GridBX )
			GridX1 = GridBX;
		if ( GridY1 > GridBY )
			GridY1 = GridBY;

			
		// Bottom corner of the grid //
		int GridX2 = GridAX + GridA.Width();
		int GridY2 = GridAY + GridA.Height();
		
		if ( GridX2 < (int)(GridBX + GridB.Width()) )
			GridX2 = GridBX + GridB.Width();
		if ( GridY2 < (int)(GridBY + GridB.Height()) )
			GridY2 = GridBY + GridB.Height();

		
		// Calculate the dimensions //
		int Width = GridX2 - GridX1;
		int Height = GridY2 - GridY1;

		
		// Calculate Start Positions //
		int AX = GridAX - GridX1;
		int AY = GridAY - GridY1;
		int BX = GridBX - GridX1;
		int BY = GridBY - GridY1;
			
		// Create a Grid to hold our copy //
		Grid2D< tType > NewGrid( Width, Height, InitValue );

		// Copy GridA //
		for ( size_t _y = GridA.Height(); _y--; ) {
			for ( size_t _x = GridA.Width(); _x--; ) {
				if ( GridA( _x, _y ) == TestValue )
					NewGrid( AX + _x, AY + _y ) = GridA( _x, _y );
			}
		}

		// Copy GridB //
		for ( size_t _y = GridB.Height(); _y--; ) {
			for ( size_t _x = GridB.Width(); _x--; ) {
				if ( GridB( _x, _y ) == TestValue )
					NewGrid( BX + _x, BY + _y ) = GridB( _x, _y );
			}
		}
		
		// Return the grid //
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D< tType > MergeBlendOnlyMask(
		const Grid2D< tType >& GridA,
		const Grid2D< tType >& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& TestValue = tType(),
		const tType& MaskValue = tType(),
		const tType& InitValue = tType()
		)
	{
		// Top corner of the grid //
		int GridX1 = GridAX;
		int GridY1 = GridAY;
		
		if ( GridX1 > GridBX )
			GridX1 = GridBX;
		if ( GridY1 > GridBY )
			GridY1 = GridBY;

			
		// Bottom corner of the grid //
		int GridX2 = GridAX + GridA.Width();
		int GridY2 = GridAY + GridA.Height();
		
		if ( GridX2 < (int)(GridBX + GridB.Width()) )
			GridX2 = GridBX + GridB.Width();
		if ( GridY2 < (int)(GridBY + GridB.Height()) )
			GridY2 = GridBY + GridB.Height();

		
		// Calculate the dimensions //
		int Width = GridX2 - GridX1;
		int Height = GridY2 - GridY1;

		
		// Calculate Start Positions //
		int AX = GridAX - GridX1;
		int AY = GridAY - GridY1;
		int BX = GridBX - GridX1;
		int BY = GridBY - GridY1;
			
		// Create a Grid to hold our copy //
		Grid2D< tType > NewGrid( Width, Height, InitValue );

		// Copy GridA //
		for ( size_t _y = GridA.Height(); _y--; ) {
			for ( size_t _x = GridA.Width(); _x--; ) {
				if ( GridA( _x, _y ) == TestValue )
					NewGrid( AX + _x, AY + _y ) = MaskValue;
			}
		}

		// Copy GridB //
		for ( size_t _y = GridB.Height(); _y--; ) {
			for ( size_t _x = GridB.Width(); _x--; ) {
				if ( GridB( _x, _y ) == TestValue )
					NewGrid( BX + _x, BY + _y ) = MaskValue;
			}
		}
		
		// Return the grid //
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D< tType > MergeBlendMask(
		const Grid2D< tType >& GridA,
		const Grid2D< tType >& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& TestValue = tType(),
		const tType& MaskValue = tType(),
		const tType& InitValue = tType()
		)
	{
		// Top corner of the grid //
		int GridX1 = GridAX;
		int GridY1 = GridAY;
		
		if ( GridX1 > GridBX )
			GridX1 = GridBX;
		if ( GridY1 > GridBY )
			GridY1 = GridBY;

			
		// Bottom corner of the grid //
		int GridX2 = GridAX + GridA.Width();
		int GridY2 = GridAY + GridA.Height();
		
		if ( GridX2 < (int)(GridBX + GridB.Width()) )
			GridX2 = GridBX + GridB.Width();
		if ( GridY2 < (int)(GridBY + GridB.Height()) )
			GridY2 = GridBY + GridB.Height();

		
		// Calculate the dimensions //
		int Width = GridX2 - GridX1;
		int Height = GridY2 - GridY1;

		
		// Calculate Start Positions //
		int AX = GridAX - GridX1;
		int AY = GridAY - GridY1;
		int BX = GridBX - GridX1;
		int BY = GridBY - GridY1;
			
		// Create a Grid to hold our copy //
		Grid2D< tType > NewGrid( Width, Height, InitValue );

		// Copy GridA //
		for ( size_t _y = GridA.Height(); _y--; ) {
			for ( size_t _x = GridA.Width(); _x--; ) {
				if ( GridA( _x, _y ) != TestValue )
					NewGrid( AX + _x, AY + _y ) = MaskValue;
			}
		}

		// Copy GridB //
		for ( size_t _y = GridB.Height(); _y--; ) {
			for ( size_t _x = GridB.Width(); _x--; ) {
				if ( GridB( _x, _y ) != TestValue )
					NewGrid( BX + _x, BY + _y ) = MaskValue;
			}
		}
		
		// Return the grid //
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D< tType > RotateCW( const Grid2D< tType >& Src ) {
		Grid2D< tType > NewGrid( Src.Height(), Src.Width() );
		
		size_t SrcHeight = Src.Height();
		for ( size_t _y = SrcHeight; _y--; ) {
			for ( size_t _x = Src.Width(); _x--; ) {
				NewGrid( (SrcHeight-1)-_y, _x ) = Src( _x, _y );
			}
		}		
		
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D< tType > RotateCCW( const Grid2D< tType >& Src ) {
		Grid2D< tType > NewGrid( Src.Height(), Src.Width() );
		
		size_t SrcWidth = Src.Width();
		for ( size_t _y = Src.Height(); _y--; ) {
			for ( size_t _x = SrcWidth; _x--; ) {
				NewGrid( _y, (SrcWidth-1)-_x ) = Src( _x, _y );
			}
		}		
		
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D< tType > RotateCW( ) {
		return RotateCW( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D< tType > RotateCCW( ) {
		return RotateCCW( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D< tType > FlipX( const Grid2D< tType >& Src ) {
		Grid2D< tType > NewGrid( Src.Width(), Src.Height() );
		
		size_t SrcWidth = Src.Width();
		size_t SrcHeight = Src.Height();
		for ( size_t _y = SrcHeight; _y--; ) {
			for ( size_t _x = SrcWidth; _x--; ) {
				NewGrid( (SrcWidth-1)-_x, _y ) = Src( _x, _y );
			}
		}		
		
		return NewGrid;		
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D< tType > FlipY( const Grid2D< tType >& Src ) {
		Grid2D< tType > NewGrid( Width(), Height() );
		
		size_t SrcWidth = Width();
		size_t SrcHeight = Height();
		for ( size_t _y = SrcHeight; _y--; ) {
			for ( size_t _x = SrcWidth; _x--; ) {
				NewGrid( _x, (SrcHeight-1)-_y ) = Src( _x, _y );
			}
		}		
		
		return NewGrid;		
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D< tType > FlipX( ) {
		return FlipX( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D< tType > FlipY( ) {
		return FlipY( *this );
	}
	// - -------------------------------------------------------------------------------------- - //	
	inline const Grid2D< tType > Trim( const Grid2D< tType >& Src, const tType& Zero = tType() ) {
		size_t x1, y1;
		size_t x2, y2;
		
		// Trim the left side //
		{
			bool BlockFound = false;
			for ( size_t _x = 0; _x < Src.Width(); _x++ ) {
				x1 = _x;
				// For every item in the vertical row //
				for ( size_t _y = Src.Height(); _y--; ) {
					// Test if it's not our zero //
					if ( Src( _x, _y ) != Zero )
						BlockFound = true;
				}
				// If a block was found, bail from this //
				if ( BlockFound )
					break;
			}
		}

		// Trim the right side //
		{
			bool BlockFound = false;
			for ( size_t _x = Src.Width() - 1; _x >= 0; _x-- ) {
				x2 = _x;
				// For every item in the vertical row //
				for ( size_t _y = Src.Height(); _y--; ) {
					// Test if it's not our zero //
					if ( Src( _x, _y ) != Zero )
						BlockFound = true;
				}
				// If a block was found, bail from this //
				if ( BlockFound )
					break;
			}
		}

		// Trim the top side //
		{
			bool BlockFound = false;
			for ( size_t _y = 0; _y < Src.Height(); _y++ ) {
				y1 = _y;
				// For every item in the vertical row //
				for ( size_t _x = Src.Width(); _x--; ) {
					// Test if it's not our zero //
					if ( Src( _x, _y ) != Zero )
						BlockFound = true;
				}
				// If a block was found, bail from this //
				if ( BlockFound )
					break;
			}
		}

		// Trim the bottom side //
		{
			bool BlockFound = false;
			for ( size_t _y = Src.Height() - 1; _y >= 0; _y-- ) {
				y2 = _y;
				// For every item in the vertical row //
				for ( size_t _x = Src.Width(); _x--; ) {
					// Test if it's not our zero //
					if ( Src( _x, _y ) != Zero )
						BlockFound = true;
				}
				// If a block was found, bail from this //
				if ( BlockFound )
					break;
			}
		}

		size_t NewWidth = x2 + 1 - x1;
		size_t NewHeight = y2 + 1 - y1;
	
		return Copy( Src, NewWidth, NewHeight, x1, y1, 0, 0 );
	}
		
public:
	// - -------------------------------------------------------------------------------------- - //
	inline void Resize( const size_t NewWidth, const size_t NewHeight, const tType& InitValue = tType() ) {
		ResizeCenter( NewWidth, NewHeight, InitValue );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void ResizeCenter( const size_t NewWidth, const size_t NewHeight, const tType& InitValue = tType() ) {
		int SrcStartX;
		int DestStartX;

		// Center the X //
		if ( NewWidth > w ) {
			SrcStartX = 0;
			DestStartX = (NewWidth - Width()) >> 1;
		}
		else {
			SrcStartX = (Width() - NewWidth) >> 1;
			DestStartX = 0;
		}
		
		
		int SrcStartY;
		int DestStartY;

		// Center the Y //
		if ( NewHeight > h ) {
			SrcStartY = 0;
			DestStartY = (NewHeight - Height()) >> 1;
		}
		else {
			SrcStartY = (Height() - NewHeight) >> 1;
			DestStartY = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, NewHeight, SrcStartX, SrcStartY, DestStartX, DestStartY, InitValue ) );
		w = NewWidth;
		h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void ResizeAlign( const size_t NewWidth, const size_t NewHeight, const int XAlign, const int YAlign, const tType& InitValue = tType() ) {
		int SrcStartX;
		int DestStartX;

		// Align the X Axis //
		if ( XAlign == 0 ) {
			// Center the X //
			if ( NewWidth > w ) {
				SrcStartX = 0;
				DestStartX = (NewWidth - Width()) >> 1;
			}
			else {
				SrcStartX = (Width() - NewWidth) >> 1;
				DestStartX = 0;
			}
		}
		else if ( XAlign < 0 ) {
			// Left Align the Positions //
			SrcStartX = 0;
			DestStartX = 0;
		}
		else if ( XAlign > 0 ) {
			// Right Align the Positions //
			if ( NewWidth > w ) {
				SrcStartX = 0;
				DestStartX = (NewWidth - Width());
			}
			else {
				SrcStartX = (Width() - NewWidth);
				DestStartX = 0;
			}			
		}
		
		
		int SrcStartY;
		int DestStartY;

		// Align the Y Axis //
		if ( YAlign == 0 ) {
			// Center the Y //
			if ( NewHeight > h ) {
				SrcStartY = 0;
				DestStartY = (NewHeight - Height()) >> 1;
			}
			else {
				SrcStartY = (Height() - NewHeight) >> 1;
				DestStartY = 0;
			}
		}
		else if ( YAlign < 0 ) {
			// Left Align the Positions //
			SrcStartY = 0;
			DestStartY = 0;
		}
		else if ( YAlign > 0 ) {
			// Right Align the Positions //
			if ( NewHeight > h ) {
				SrcStartY = 0;
				DestStartY = (NewHeight - Height());
			}
			else {
				SrcStartY = (Height() - NewHeight);
				DestStartY = 0;
			}	
		}		
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, NewHeight, SrcStartX, SrcStartY, DestStartX, DestStartY, InitValue ) );
		w = NewWidth;
		h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidth( const size_t NewWidth, const tType& InitValue = tType() ) {
		SetWidthCenter( NewWidth, InitValue );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidthCenter( const size_t NewWidth, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Center the Positions //
		if ( NewWidth > w ) {
			SrcStart = 0;
			DestStart = (NewWidth - Width()) >> 1;
		}
		else {
			SrcStart = (Width() - NewWidth) >> 1;
			DestStart = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, h, SrcStart, 0, DestStart, 0, InitValue ) );
		w = NewWidth;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidthLeft( const size_t NewWidth, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Left Align the Positions //
		SrcStart = 0;
		DestStart = 0;

		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, h, SrcStart, 0, DestStart, 0, InitValue ) );
		w = NewWidth;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidthRight( const size_t NewWidth, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Right Align the Positions //
		if ( NewWidth > w ) {
			SrcStart = 0;
			DestStart = (NewWidth - Width());
		}
		else {
			SrcStart = (Width() - NewWidth);
			DestStart = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, h, SrcStart, 0, DestStart, 0, InitValue ) );
		w = NewWidth;
	}
	// - -------------------------------------------------------------------------------------- - //
	

	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeight( const size_t NewHeight, const tType& InitValue = tType() ) {
		SetHeightCenter( NewHeight, InitValue );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeightCenter( const size_t NewHeight, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Center the Positions //
		if ( NewHeight > h ) {
			SrcStart = 0;
			DestStart = (NewHeight - Height()) >> 1;
		}
		else {
			SrcStart = (Height() - NewHeight) >> 1;
			DestStart = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, w, NewHeight, 0, SrcStart, 0, DestStart, InitValue ) );
		h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeightTop( const size_t NewHeight, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Left Align the Positions //
		SrcStart = 0;
		DestStart = 0;

		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, w, NewHeight, 0, SrcStart, 0, DestStart, InitValue ) );
		h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeightBottom( const size_t NewHeight, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Right Align the Positions //
		if ( NewHeight > h ) {
			SrcStart = 0;
			DestStart = (NewHeight - Height());
		}
		else {
			SrcStart = (Height() - NewHeight);
			DestStart = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, w, NewHeight, 0, SrcStart, 0, DestStart, InitValue ) );
		h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of instances of a value //
	inline const size_t Count( const tType& Value ) {
		size_t CurrentCount = 0;

		for ( size_t _y = Height(); _y--; ) {
			for ( size_t _x = Width(); _x--; ) {
				if ( *this( _x, _y ) == Value )
					CurrentCount++;
			}
		}	
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of non instances of a value //
	inline const size_t CountNot( const tType& Value ) {
		size_t CurrentCount = 0;

		for ( size_t _y = Height(); _y--; ) {
			for ( size_t _x = Width(); _x--; ) {
				if ( *this( _x, _y ) != Value )
					CurrentCount++;
			}
		}	
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Grid_Grid2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
