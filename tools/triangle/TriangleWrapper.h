#pragma once
#include <string>
#include <Core/EigenTypedef.h>

class TriangleWrapper {
    public:
        TriangleWrapper(const MatrixFr& points, const MatrixIr& segments) : 
            m_points(points), m_segments(segments) {}

    public:
        /**
         * Set hole points.  Used by triangle to flood and remove faces
         * representing holes.
         *
         * One can get by without setting holes by setting the
         * auto_hole_detection flag in run(...).
         */
        void set_holes(const MatrixFr& holes) { m_holes = holes; }

        /**
         * Depending on the column of segments, either triangulate a PLSG or
         * refine an existing triangulation.
         */
        void run(Float max_area,
                bool split_boundary=true,
                bool auto_hole_detection=false);

        MatrixFr get_vertices() const { return m_vertices; }
        MatrixIr get_faces() const { return m_faces; }

    protected:
        void run_triangle(
                const MatrixFr& points,
                const MatrixIr& segments,
                const MatrixFr& holes,
                const std::string& flags);
        void refine(
                const MatrixFr& points,
                const MatrixIr& faces,
                const std::string& flags);
        void poke_holes();

    private:
        // Input data
        MatrixFr m_points;
        MatrixFr m_holes;
        MatrixIr m_segments;

        // Output data
        MatrixFr m_vertices;
        MatrixIr m_faces;
        MatrixIr m_face_neighbors;
        VectorI  m_edges;
        VectorI  m_edge_marks;
};
