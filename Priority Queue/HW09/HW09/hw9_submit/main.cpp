#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>

#include "image.h"
#include "priority_queue.h"
using namespace std;
// ===================================================================================================

// distance field method functions
double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image);
double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image);

// visualization style helper functions
Color Rainbow(double distance, double max_distance);
Color GreyBands(double distance, double max_distance, int num_bands);

// ===================================================================================================

int main(int argc, char* argv[]) {
  if (argc != 5) {
    std::cerr << "Usage: " << argv[0] << " input.ppm output.ppm distance_field_method visualization_style" << std::endl;
    exit(1);
  }

  // open the input image
  //--------------------------------------------------------------------------
  Image<Color> input;
  //--------------------------------------------------------------------------
    
  if (!input.Load(argv[1])) {
    std::cerr << "ERROR: Cannot open input file: " << argv[1] << std::endl;
    exit(1);
  }

  // a place to write the distance values
  Image<DistancePixel> distance_image;
  distance_image.Allocate(input.Width(),input.Height());

  // calculate the distance field (each function returns the maximum distance value)
  double max_distance = 0;
  if (std::string(argv[3]) == std::string("naive_method")) {
    max_distance = NaiveDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("improved_method")) {
    max_distance = ImprovedDistanceFieldMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_map")) {
    max_distance = FastMarchingMethod(input,distance_image);
  } else if (std::string(argv[3]) == std::string("pq_with_hash_table")) {
    // EXTRA CREDIT: implement FastMarchingMethod with a hash table
  } else {
    std::cerr << "ERROR: Unknown distance field method: " << argv[3] << std::endl;
    exit(1);
  }

  // convert distance values to a visualization
  Image<Color> output;
  output.Allocate(input.Width(),input.Height());
  for (int i = 0; i < input.Width(); i++) {
    for (int j = 0; j < input.Height(); j++) {
      double v = distance_image.GetPixel(i,j).getValue();
      if (std::string(argv[4]) == std::string("greyscale")) {
	output.SetPixel(i,j,GreyBands(v,max_distance*1.01,1));
      } else if (std::string(argv[4]) == std::string("grey_bands")) {
	output.SetPixel(i,j,GreyBands(v,max_distance,4));
      } else if (std::string(argv[4]) == std::string("rainbow")) {
	output.SetPixel(i,j,Rainbow(v,max_distance));
      } else {
	// EXTRA CREDIT: create other visualizations 
	std::cerr << "ERROR: Unknown visualization style" << std::endl;
	exit(0);
      }
    }
  }
  // save output
  if (!output.Save(argv[2])) {
    std::cerr << "ERROR: Cannot save to output file: " << argv[2] << std::endl;
    exit(1);
  }

  return 0;
}

// ===================================================================================================

double NaiveDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  int w = input.Width();
  int h = input.Height();
  // return the maximum distance value
  double answer = 0;
  // loop over the pixels in the input image
  for (int i = 0; i < w; i++)  {
    for (int j = 0; j < h; j++) {
      double closest = -1;      
      // loop over all other pixels in the input image
      for (int i2 = 0; i2 < w; i2++)  {
	     for (int j2 = 0; j2 < h; j2++) {
	         const Color& c = input.GetPixel(i2,j2);
	         // skip all pixels that are not black
	         if (!c.isBlack()) continue;
             // calculate the distance between the two pixels
	         double distance = sqrt((i-i2)*(i-i2) + (j-j2)*(j-j2));
	         // store the closest distance to a black pixel
	         if (closest < 0 || distance < closest) {
	             closest = distance;
	         }
	      }
      }
      assert (closest >= 0);
      answer = std::max(answer,closest);
      // save the data to the distance image
      DistancePixel& p = distance_image.GetPixel(i,j);
      p.setValue(closest);
    }
  }
    return answer;
}


double ImprovedDistanceFieldMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {

  //
  // IMPLEMENT THIS FUNCTION
  //
  // a small improvement on the NaiveDistanceFieldMethod
  //
    int w = input.Width();
    int h = input.Height();
    // return the maximum distance value
    double answer = 0;
    
    // First, find those black pixels in the imput image.
    vector<DistancePixel> Black_Position;
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            const Color& c = input.GetPixel(i, j);
            // Skip all pixels that are not black
            if (c.isBlack()) Black_Position.push_back(DistancePixel(i,j,0,1));
        }
    }
    
    // Compare every pixel to every black pixel.
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            double closest = -1;
            // loop over all black pixels in the input image
            for (int p = 0; p < Black_Position.size(); ++p) {
                DistancePixel temp_black = Black_Position[p];
                int temp_x = temp_black.getX();
                int temp_y = temp_black.getY();
                double distance = sqrt((i-temp_x)*(i-temp_x) + (j-temp_y)*(j-temp_y));
                if (closest < 0 || distance < closest){
                    closest = distance;
                }
            }
            assert(closest >= 0);
            answer = std::max(answer,closest);
            // save the data to the distance image
            DistancePixel& p = distance_image.GetPixel(i,j);
            p.setValue(closest);
        }
    }
    return answer;

}

double FastMarchingMethod(Image<Color> &input, Image<DistancePixel> &distance_image) {
  // IMPLEMENT THIS FUNCTION
  // (using the advancing front method, and a priority queue)
    int w = input.Width();
    int h = input.Height();
    // return the maximum distance value
    double max_distance = 0;
    // Initialize the coordinates in distance_image:
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            DistancePixel& temp_pixel = distance_image.GetPixel(i, j);
            temp_pixel.setX(i);
            temp_pixel.setY(j);
        }
    }
    // Initialize the distance field value of black pixels to 0;
    std::vector<DistancePixel> black_pixels;
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            const Color& c = input.GetPixel(i, j);
            // Skip all pixels that are not black
            if (c.isBlack()) {
                DistancePixel& black = distance_image.GetPixel(i, j);
                black.setValue(0);
                black.set_black(true);
                black_pixels.push_back(black);
            }
        }
    }
    
    // Create a vector that is used to construct the priority queue:
    // --------------------------------------------------------------
    std::vector<DistancePixel*> values;
    // --------------------------------------------------------------
    // Calculate the 8 neighboring pixels' distances of each black pixels and set them:
    for (unsigned int i = 0; i < black_pixels.size(); ++i) {
    //--------------------------------------------------------------------------------
        int temp_black_X = black_pixels[i].getX();
        int temp_black_Y = black_pixels[i].getY();
        for (int k = temp_black_X - 1; k <= temp_black_X + 1; ++k) {
            for (int l = temp_black_Y - 1; l <= temp_black_Y + 1; ++l) {
                // Check whether it is beyond the edge
                if (k < 0 || l < 0 || k > w - 1 || l > h - 1) continue;
                if (k == temp_black_X && l == temp_black_Y) continue;
                // Check whether it is black pixel
                if (input.GetPixel(k, l).isBlack()) continue;
                // Calculate the distance
                double temp_distance = sqrt((k - temp_black_X)*(k - temp_black_X) +
                                            (l - temp_black_Y)*(l - temp_black_Y));
                // If the Calulated distance is less than its orginal distance
                // ------------------------------------------------------------
                DistancePixel& q = distance_image.GetPixel(k, l);
                if (temp_distance < q.getValue()) {
                    q.setValue(temp_distance);
                    if (temp_distance == 1) q.set_black(true);
                }
                DistancePixel* temp_pixel = &distance_image.GetPixel(k, l);
                // Check whether this pixel is already in the values:
                if (i == 0) {
                    values.push_back(temp_pixel);
                } else {
                    bool found = false;
                    for (int m = 0; m < values.size(); ++m) {
                        // If the DistancePixel's pointer is already in the vector
                        // then we don't need to push it in.
                        if (k == values[m]->getX() && l == values[m]->getY()) {
                            found = true;
                        }
                    }
                    if (!found) {
                        values.push_back(temp_pixel);
                    }
                }
            }
        }
     //--------------------------------------------------------------------------------
    }
    
    // Place the newly_updated pixels into a priority queue, using the distance value
    // as the prioriy queue:
    //-----------------------------------------------------------------
    DistancePixel_PriorityQueue D_prirityQueue(values);
    //-----------------------------------------------------------------
    
    // Propagating:
    while (! D_prirityQueue.empty()) {
        DistancePixel* top = D_prirityQueue.top();
        top->set_black(true);
        D_prirityQueue.pop();
        int temp_x = top->getX();
        int temp_y = top->getY();
        for (int i = temp_x - 1; i <= temp_x + 1; ++i) {
            for (int j = temp_y - 1; j <= temp_y + 1; ++j) {
                if (i < 0 || j < 0 || i > w - 1 || j > h - 1) continue;
                if (i == temp_x && j == temp_y) continue;
                // If the pixel is black, we can just ignore it:
                if (distance_image.GetPixel(i, j).get_black()) continue;
                
                double temp_distance = sqrt((temp_x - i)*(temp_x - i) + (temp_y - j)*(temp_y - j));
                // If the calculated distance is less than its orginal distance, set it:
                double sum_distance = top->getValue() + temp_distance;
                DistancePixel& p = distance_image.GetPixel(i, j);
                if (sum_distance < p.getValue()) {
                    p.setValue(sum_distance);
                    DistancePixel* new_element = &distance_image.GetPixel(i, j);
                    if (D_prirityQueue.in_heap(new_element)) {
                        // If the pointer is in the heap tree, we need to adjust its position:
                        D_prirityQueue.update_position(new_element);
                    } else {
                        // If not, we add it into the heap tree:
                        D_prirityQueue.push(new_element);
                    }
                }
            }
        }
    }
    // Calculate the max_distance of distance_image:
    double t_value = 0;
    for (unsigned int i = 0; i < w; ++i) {
        for (unsigned int j = 0; j < h; ++j) {
            DistancePixel pixel = distance_image.GetPixel(i, j);
            t_value = pixel.getValue();
            max_distance = std::max(max_distance, t_value);
        }
    }
    return max_distance;
}

// ===================================================================================================

Color Rainbow(double distance, double max_distance) {
  Color answer;
  if (distance < 0.001) {
    // black
    answer.r = 0; answer.g = 0; answer.b = 0;
  } else if (distance < 0.2*max_distance) {
    // blue -> cyan
    double tmp = distance * 5.0 / max_distance;
    answer.r = 0;
    answer.g = tmp*255;
    answer.b = 255;
  } else if (distance < 0.4*max_distance) {
    // cyan -> green
    double tmp = (distance-0.2*max_distance) * 5.0 / max_distance;
    answer.r = 0;
    answer.g = 255;
    answer.b = (1-tmp*tmp)*255;
  } else if (distance < 0.6*max_distance) {
    // green -> yellow
    double tmp = (distance-0.4*max_distance) * 5.0 / max_distance;
    answer.r = sqrt(tmp)*255;
    answer.g = 255;
    answer.b = 0;
  } else if (distance < 0.8*max_distance) {
    // yellow -> red
    double tmp = (distance-0.6*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = (1-tmp*tmp)*255;
    answer.b = 0;
  } else if (distance < max_distance) {
    // red -> white
    double tmp = (distance-0.8*max_distance) * 5.0 / max_distance;
    answer.r = 255;
    answer.g = tmp*255;
    answer.b = tmp*255;
  } else {
    // white
    answer.r = answer.g = answer.b = 255;
  }  
  return answer;
}

Color GreyBands(double distance, double max_value, int num_bands) {
  Color answer;
  if (distance < 0.001) {
    // red
    answer.r = 255; answer.g = 0; answer.b = 0;
  } else {
    // shades of grey
    answer.r = answer.g = answer.b = int(num_bands*256*distance/double(max_value)) % 256;
  }  
  return answer;
}

// ===================================================================================================
