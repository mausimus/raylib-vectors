#pragma once

class VectorObject
{
    public:
        VectorObject();
        void AddLine(float sx, float sy, float ex, float ey);
        void Center(float x, float y); // center specific coord
        void CenterY(float y); // center y only for text
        void Center(); // auto center bounding box
        void Flip(int x, int y);
        void Scale(float s); // scale
        void Render(float thick);
        void Draw(Color color);

        // Inkscape
        void moveTo(double x, double y);
        void lineTo(double x, double y);

        // multiple cached versions per thickness?
        float _thick;
        float _width;
        float _height;
        bool _solid;

        static VectorObject* Rectangle(float w, float h);
        static VectorObject* Triangle(float w, float h);
        static VectorObject* Regular(float r, int n);
        static VectorObject* Circle(float r);

    private:
        void RenderLine(float sx, float sy, float ex, float ey, float thick);
        void RenderSolid();

        float _x; // temporary during construction
        float _y;

        float _s; // scale
        float _cx; // center
        float _cy;

        std::vector<Vector4> lines; // source lines        
        std::vector<Vector2> vertices; // rendered triangles
        std::vector<Vector2> solids; // rendered solids
        std::vector<float> lengths;
};

class CompositeObject
{
    public:
        void AddObject(VectorObject *object, Vector2 position, float rotation, Color color);
        
        std::vector<VectorObject*> _objects;
        std::vector<Color> _colors;
        std::vector<Vector2> _positions;
        std::vector<float> _rotations;
};

class VectorBatch
{
    public:
        VectorBatch();
        void DrawObject(VectorObject* obj, Vector2 pos, float rot, Color color);
        void DrawObject(CompositeObject* obj, Vector2 pos, float rot);
        void DrawLine(float sx, float sy, float ex, float ey, Color color); // ad-hoc, slow!
        void Begin();
        void End();        

        void Thick(float thick);

    //private:
        float _thick;
};
