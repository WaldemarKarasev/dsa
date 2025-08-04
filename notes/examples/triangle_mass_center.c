

struct Point
{
    float x;
    float y;
};

struct Triangle
{
    Point points[3];
};

    // Triangle(std::array<Point, 3> points) : points_{std::move(points)} {}

    // std::array<Point, 3> points_;

    // void print() const
    // {
    //     std::cout << "Triangle:" << std::endl;
    //     for (const auto& point : points_)
    //     {
    //         point.print();
    //     }
    // }

    // Point find_median() const
    // {
    //     Point med{};
    //     for (const auto& point : points_)
    //     {
    //         med.x += point.x;
    //         med.y += point.y;
    //     }

    //     med.x = med.x / 3;
    //     med.y = med.y / 3;

    //     return med;
    // }

Triangle ReadTriangle(std::string input_filename)
{
    Point p1;
    Point p2;
    Point p3;

    std::ifstream file(input_filename);
    
    std::array<Point, 3> points;
    if (file.is_open())
    {
        float x, y;
        int counter = 0;
        while (file >> x >> y)
        {
            if (counter > 3) break;
            points[counter] = Point{x, y};
            ++counter;
        }
        
    }

    return Triangle(std::move(points));
}

void WriteToFile(std::string output_filename, Point p)
{
    std::ofstream output(output_filename);

    if (output.is_open())
    {
        output << p.x << " " << p.y << std::endl;
    }
}

int main()
{
    Triangle triangle = ReadTriangle("input.txt");
    WriteToFile("output.txt", triangle.find_median());
}
