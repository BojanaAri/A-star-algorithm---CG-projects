////
//// Created by Bojana on 02-Oct-23.
////
//#include <OpenGLPrj.hpp>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//
//#include <Shader.hpp>
//#include <Square.h>
//#include <Camera.hpp>
//
//#include <iostream>
//#include <string>
//#include <queue>
//
//using namespace std;
//
//const std::string program_name = ("A* algorithm");
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 800;
//
//
//void framebuffer_size_callback(GLFWwindow *window, int width, int height);
//void mouse_callback(GLFWwindow *window, double xpos, double ypos);
//void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//void getRayFromMouse(double xPos, double yPos, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::vec3 &rayDirection, glm::vec3 &rayOrigin);
//bool testRayOBBIntersection(
//        glm::vec3 rayOrigin,        // Ray origin, in world space
//        glm::vec3 rayDirection,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
//        glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
//        glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
//        glm::mat4 modelMatrix      // Transformation applied to the mesh (which will thus be also applied to its bounding box)
//);
//void makeGrid(::int32_t, ::int32_t);
//int heuristicFunction(const Square& m1, const Square& m2);
//void makePath(::int32_t x, ::int32_t y);
//bool algorithm();
//
//// variables
//int32_t nr, nc, rows = 20, cols = 20;
//Square m[20][20];
//Square startSquare, endSquare;
//
//bool start = true;
//bool End = true;
//
//// camera
//static Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//static float lastX = SCR_WIDTH / 2.0f;
//static float lastY = SCR_HEIGHT / 2.0f;
//static bool firstMouse = true;
//
//// timing
//static float deltaTime = 0.0f; // time between current frame and last frame
//static float lastFrame = 0.0f;
//
//
//int main() {
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(
//        GLFW_OPENGL_FORWARD_COMPAT,
//        GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
//                                          program_name.c_str(), nullptr, nullptr);
//
//    if (window == nullptr) {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    glEnable(GL_DEPTH_TEST);
//    //--------------------------------------------------------------------------------------------------
//    //
//    std::string shader_location("../res/shaders/");
//
//    std::string used_shaders("shader");
//    Shader ourShader(shader_location + used_shaders + std::string(".vert"),
//                     shader_location + used_shaders + std::string(".frag"));
//
//    ////////////////////////////////////////////////////////////////////////////////////
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//
//    ///////////////////
//    float vertices[] = {
//            -0.05f, -0.05f, -0.05f,  0.05f,  -0.05f, -0.05f,
//            0.05f,  0.05f,  -0.05f, 0.05f,  0.05f,  -0.05f,
//            -0.05f, 0.05f,  -0.05f, -0.05f, -0.05f, -0.05f,
//
//            -0.05f, -0.05f, 0.05f,  0.05f,  -0.05f, 0.05f,
//            0.05f,  0.05f,  0.05f,  0.05f,  0.05f,  0.05f,
//            -0.05f, 0.05f,  0.05f,   -0.05f, -0.05f, 0.05f,
//
//            -0.05f, 0.05f,  0.05f,  -0.05f, 0.05f,  -0.05f,
//            -0.05f, -0.05f, -0.05f, -0.05f, -0.05f, -0.05f,
//            -0.05f, -0.05f, 0.05f,  -0.05f, 0.05f,  0.05f,
//
//            0.05f,  0.05f,  0.05f,  0.05f,  0.05f,  -0.05f,
//            0.05f,  -0.05f, -0.05f, 0.05f,  -0.05f, -0.05f,
//            0.05f,  -0.05f, 0.05f,  0.05f,  0.05f,  0.05f,
//
//            -0.05f, -0.05f, -0.05f, 0.05f,  -0.05f, -0.05f,
//            0.05f,  -0.05f, 0.05f,  0.05f,  -0.05f, 0.05f,
//            -0.05f, -0.05f, 0.05f,   -0.05f, -0.05f, -0.05f,
//
//            -0.05f, 0.05f,  -0.05f, 0.05f,  0.05f,  -0.05f,
//            0.05f,  0.05f,  0.05f,   0.05f,  0.05f,  0.05f,
//            -0.05f, 0.05f,  0.05f,-0.05f, 0.05f,  -0.05f };
//
//
//    unsigned int VBO, VAO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // position attribute
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
//                          static_cast<void *>(nullptr));
//    glEnableVertexAttribArray(0);
//
//    nr = nc = 8;
//    makeGrid(rows,cols);
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window)) {
//        // per-frame time logic
//        // --------------------
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----
//        processInput(window);
//
//        // create transformations
//        glm::mat4 projection = camera.GetProjectionMatrix();
//        glm::mat4 view = camera.GetViewMatrix();
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        ourShader.use();
//        glBindVertexArray(VAO);
//
//        ourShader.setMat4("projection",projection);
//        ourShader.setMat4("view", view);
//
//        for (int i = 0; i < rows; i++) {
//            for (int j = 0; j < cols; j++) {
//                glm::mat4 model = glm::mat4(1.0f);
//
//                float xcoord = ((float) m[i][j].x / nr - 1.18f);
//                float ycoord = 2.18-( (float) m[i][j].y / nc + 1.0f);
//
//                model = glm::translate(model, glm::vec3(xcoord, ycoord, 0.0f));
//
//                glm::vec4 uni;
//                if(m[i][j].sType == SQUARE_TYPE::START) {
//                    int st = glGetUniformLocation(ourShader.ID, "colorS");
//                    uni = m[i][j].color();
//                    glUniform4f(st, uni.x, uni.y, uni.z, uni.w);
//                    start = false;
//                    startSquare = m[i][j];
//                }
//
//                if(m[i][j].sType == SQUARE_TYPE::END) {
//                    int e = glGetUniformLocation(ourShader.ID, "colorE");
//                    uni = m[i][j].color();
//                    glUniform4f(e, uni.x, uni.y, uni.z, uni.w);
//                    End = false;
//                    endSquare = m[i][j];
//                }
//
//                if(m[i][j].sType == SQUARE_TYPE::PATH) {
//                    int e = glGetUniformLocation(ourShader.ID, "open");
//                    uni = m[i][j].color();
//                    glUniform4f(e, uni.x, uni.y, uni.z, uni.w);
//                }
//
//                int colorLocation = glGetUniformLocation(ourShader.ID, "color");
//                uni = m[i][j].color();
//                glUniform4f(colorLocation, uni.x , uni.y, uni.z, uni.w);
//
//                ourShader.setMat4("model", model);
//                glDrawArrays(GL_TRIANGLES, 0, 36);
//            }
//        }
//         // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved
//        // etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//
//// process all input: query GLFW whether relevant keys are pressed/released this
//// frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//
//void processInput(GLFWwindow *window) {
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//
//    double xpos, ypos;
//    if( glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
//        glfwGetCursorPos(window, &xpos, &ypos);
//        glm::vec3 rayDirection,rayOrigin;
//
//        getRayFromMouse(xpos,SCR_HEIGHT-ypos,
//                        camera.GetProjectionMatrix(),
//                        camera.GetViewMatrix(),
//                        rayDirection,rayOrigin);
//
//        glm::vec3 aabb_min(-0.05f, -0.05f, -0.05f);
//        glm::vec3 aabb_max( 0.05f,  0.05f,  0.05f);
//
//        for (int i = 0; i < rows; i++) {
//            for (int j = 0; j < cols; j++) {
//                float xcoord = ((float) m[i][j].x / nr - 1.18f);
//                float ycoord = 2.18-( (float) m[i][j].y / nc + 1.0f);
//
//                glm::mat4 model = glm::mat4(1.0f);
//                model = glm::translate(model, glm::vec3(xcoord, ycoord, 0.0f));
//
//                if(testRayOBBIntersection(
//                        rayOrigin,
//                        rayDirection,
//                        aabb_min,
//                        aabb_max,
//                        model))
//                {
//                    if (start && m[i][j].sType != SQUARE_TYPE::END) {
//                        m[i][j].sType = SQUARE_TYPE::START;
//                        start = false;
//                        return;
//                    }
//                    if (End && m[i][j].sType != SQUARE_TYPE::START) {
//                        m[i][j].sType = SQUARE_TYPE::END;
//                        End = false;
//                        return;
//                    }
//
//                    if (m[i][j].sType != SQUARE_TYPE::START && m[i][j].sType != SQUARE_TYPE::END
//                        &&  (i >= 0 && i < 20) && (j >= 0 && j < 20) )
//                        m[i][j].sType = SQUARE_TYPE::BARRIER;
//
//                    break;
//                }
//            }
//        }
//    }
//
//    int startAlgorithm = glfwGetKey(window, GLFW_KEY_SPACE);
//    if (startAlgorithm == GLFW_PRESS && !start && !End)
//    {
//        algorithm();
//    }
//    else if (startAlgorithm == GLFW_PRESS){
//        cout<<"Add start and end position"<<endl;
//    }
//
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback
//// function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
//    // make sure the viewport matches the new window dimensions; note that width
//    // and height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//void mouse_callback(GLFWwindow *window, double xposd, double yposd) {
//    float xpos = static_cast<float>(xposd);
//    float ypos = static_cast<float>(yposd);
//    if (firstMouse) {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset =
//            lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}
//
//// ---------------------------------------------------------------------------------------------
////                                      MAKE GRID
//
//void makeGrid(::int32_t r, ::int32_t c) {
//    for (int i = 0; i < r; i++) {
//        for (int j = 0; j < c; j++) {
//            Square x(i, j, SQUARE_TYPE::NORMAL);
//            m[i][j] = x;
//        }
//    }
//}
//// --------------------------------------------------------------------------------------------
////                             MANHATTAN HEURISTIC FUNCTION
//
//int heuristicFunction(const Square& m1, const Square& m2)
//{
//    int x1 = m1.x, y1 = m1.y;
//    int x2 = m2.x, y2 = m2.y;
//    return abs(x1-x2) + abs(y1-y2);
//}
//
//// ------------------------------------------------------------------------------------------
////                                       ALGORITHM
//
//void makePath(::int32_t x, ::int32_t y)
//{
//    while( x != startSquare.x || y != startSquare.y)
//    {
//        m[x][y].sType = SQUARE_TYPE::PATH;
//        int tempX = m[x][y].parentX;
//        int tempY = m[x][y].parentY;
//        x = tempX;
//        y = tempY;
//    }
//}
//
//int cnt = 0;
//bool algorithm()
//{
//    bool closedList[20][20] = {{false}};
//
//    m[startSquare.x][startSquare.y].fScore = heuristicFunction(startSquare, endSquare);
//    m[startSquare.x][startSquare.y].gScore = 0;
//
//    std::priority_queue<Square> openList;
//    m[startSquare.x][startSquare.y].insertionOrder = cnt;
//
//    openList.push(m[startSquare.x][startSquare.y]);
//
//    while(!openList.empty()){
//        Square current = openList.top();
//        openList.pop();
//
//        ::int32_t i = current.x, j = current.y;
//
//        if(i == endSquare.x && j == endSquare.y) {
//            makePath(current.x,current.y);
//            m[endSquare.x][endSquare.y].sType = SQUARE_TYPE::END;
//            return true;
//        }
//
//        closedList[i][j] = true;
//        int tmpGscore = current.gScore + 1;
//
//        if (i < 19 && m[i + 1][j].sType != SQUARE_TYPE::BARRIER && !closedList[i + 1][j])      // DOWN
//        {
//            int fNew =  tmpGscore + heuristicFunction(m[i+1][j],endSquare);
//
//            if(m[i+1][j].fScore == INT_MAX || m[i+1][j].fScore > fNew){
//                m[i+1][j].parentX = i;
//                m[i+1][j].parentY = j;
//
//                m[i+1][j].gScore = tmpGscore;
//                m[i+1][j].fScore = fNew;
//
//                cnt++;
//                m[i+1][j].insertionOrder = cnt;
//                openList.push(m[i+1][j]);
//            }
//        }
//
//        if(i > 0 && m[i-1][j].sType != SQUARE_TYPE::BARRIER && !closedList[i - 1][j]){    // UP
//            int fNew =  tmpGscore + heuristicFunction(m[i-1][j],endSquare);
//
//            if(m[i-1][j].fScore == INT_MAX || m[i-1][j].fScore > fNew)
//            {
//                m[i-1][j].parentX = i;
//                m[i-1][j].parentY = j;
//
//                m[i-1][j].gScore = tmpGscore;
//                m[i-1][j].fScore = fNew;
//
//                cnt++;
//                m[i-1][j].insertionOrder = cnt;
//                openList.push(m[i-1][j]);
//            }
//        }
//
//        if (j < 19 && m[i][j+1].sType != SQUARE_TYPE::BARRIER && !closedList[i][j+1]){
//            int fNew =  tmpGscore + heuristicFunction(m[i][j+1],endSquare);
//
//            if(m[i][j+1].fScore == INT_MAX || m[i][j+1].fScore > fNew) {
//                m[i][j + 1].parentX = i;
//                m[i][j + 1].parentY = j;
//
//                m[i][j + 1].gScore = tmpGscore;
//                m[i][j + 1].fScore = fNew;
//
//                cnt++;
//                m[i][j+1].insertionOrder = cnt;
//                openList.push(m[i][j+1]);
//            }
//        }
//
//        if(j > 0 && m[i][j-1].sType != SQUARE_TYPE::BARRIER && !closedList[i][j-1]){
//            int fNew =  tmpGscore + heuristicFunction(m[i][j-1],endSquare);
//
//            if(m[i][j-1].fScore == INT_MAX || m[i][j-1].fScore > fNew){
//                m[i][j-1].parentX = i;
//                m[i][j-1].parentY = j;
//
//                m[i][j-1].gScore = tmpGscore;
//                m[i][j-1].fScore = fNew;
//
//                cnt++;
//                m[i][j-1].insertionOrder = cnt;
//                openList.push(m[i][j-1]);
//            }
//        }
//    }
//
//    return false;
//}
//
//void getRayFromMouse(double xPos, double yPos, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::vec3 &rayDirection, glm::vec3 &rayOrigin)
//{
//    // We define the start & end point of the ray that will be casted through the screen
//    glm::vec4 RayPointStart_NDC(
//            ((float)xPos/(float)SCR_WIDTH  - 0.5f) * 2.0f, // [0, 800] -> [-1,1]
//            ((float)yPos/(float)SCR_HEIGHT - 0.5f) * 2.0f, // [0, 800] -> [-1,1]
//            -1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
//            1.0f);
//
//    glm::vec4 RayPointEnd_NDC(
//            ((float)xPos/(float)SCR_WIDTH  - 0.5f) * 2.0f,
//            ((float)yPos/(float)SCR_HEIGHT - 0.5f) * 2.0f,
//            0.0,
//            1.0f);
//
//    // Inverse (ProjectionMatrix) goes from Clip Space to Camera Space,
//    // While inverse(ViewMatrix) goes from Camera Space to World Space.
//    glm::mat4 inverseProjectionMatrix = glm::inverse(projectionMatrix);
//    glm::mat4 inverseViewMatrix = glm::inverse(viewMatrix);
//
//
//    glm::vec4 RayStartCamera = inverseProjectionMatrix * RayPointStart_NDC;
//    RayStartCamera /= RayStartCamera.w;
//    glm::vec4 RayStartWorld  = inverseViewMatrix * RayStartCamera;
//    RayStartWorld /= RayStartWorld .w;
//
//
//    glm::vec4 RayEndCamera  = inverseProjectionMatrix * RayPointEnd_NDC;
//    RayEndCamera  /= RayEndCamera  .w;
//    glm::vec4 RayEndWorld    = inverseViewMatrix * RayEndCamera;
//    RayEndWorld   /= RayEndWorld   .w;
//
//
//
//    glm::vec3 RayDirectionWorld(RayEndWorld - RayStartWorld);
//    RayDirectionWorld = glm::normalize(RayDirectionWorld);
//
//    rayOrigin = camera.Position;
//    rayDirection = RayDirectionWorld;
//}
//
//bool testRayOBBIntersection(
//        glm::vec3 rayOrigin,           // Ray origin, in world space
//        glm::vec3 rayDirection,       // Ray direction (NOT target position!), in world space. Must be normalize()'d.
//        glm::vec3 aabb_min,           // Minimum X,Y,Z coords of the mesh when not transformed at all.
//        glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
//        glm::mat4 modelMatrix       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
//){
//    float tMin = 0.0f;
//    float tMax = 100000.0f;
//
//    glm::vec3 OBBposition_worldspace(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
//    glm::vec3 delta = OBBposition_worldspace - rayOrigin;
//
//
//    // Test intersection with the 2 planes perpendicular to the OBB's X axis
//    {
//        glm::vec3 xaxis(modelMatrix[0].x, modelMatrix[0].y, modelMatrix[0].z);
//        float e = glm::dot(xaxis, delta);
//        float f = glm::dot(rayDirection, xaxis);
//
//        if ( fabs(f) > 0.001f ){ // Standard case
//
//            float t1 = (e+aabb_min.x)/f; // Intersection with the "left" plane
//            float t2 = (e+aabb_max.x)/f; // Intersection with the "right" plane
//            // t1 and t2 now contain distances betwen ray origin and ray-plane intersections
//
//            // We want t1 to represent the nearest intersection,
//            // so if it's not the case, invert t1 and t2
//            if (t1>t2){
//                float w=t1;t1=t2;t2=w; // swap t1 and t2
//            }
//
//            // tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
//            if ( t2 < tMax )
//                tMax = t2;
//            // tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
//            if ( t1 > tMin )
//                tMin = t1;
//
//            // And here's the trick :
//            // If "far" is closer than "near", then there is NO intersection.
//            // See the images in the tutorials for the visual explanation.
//            if (tMax < tMin )
//                return false;
//
//        }else{ // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
//            if(-e+aabb_min.x > 0.0f || -e+aabb_max.x < 0.0f)
//                return false;
//        }
//    }
//
//
//    // Test intersection with the 2 planes perpendicular to the OBB's Y axis
//    // Exactly the same thing than above.
//    {
//        glm::vec3 yaxis(modelMatrix[1].x, modelMatrix[1].y, modelMatrix[1].z);
//        float e = glm::dot(yaxis, delta);
//        float f = glm::dot(rayDirection, yaxis);
//
//        if ( fabs(f) > 0.001f ){
//
//            float t1 = (e+aabb_min.y)/f;
//            float t2 = (e+aabb_max.y)/f;
//
//            if (t1>t2){float w=t1;t1=t2;t2=w;}
//
//            if ( t2 < tMax )
//                tMax = t2;
//            if ( t1 > tMin )
//                tMin = t1;
//            if (tMin > tMax)
//                return false;
//
//        }else{
//            if(-e+aabb_min.y > 0.0f || -e+aabb_max.y < 0.0f)
//                return false;
//        }
//    }
//
//
//    // Test intersection with the 2 planes perpendicular to the OBB's Z axis
//    // Exactly the same thing than above.
//    {
//        glm::vec3 zaxis(modelMatrix[2].x, modelMatrix[2].y, modelMatrix[2].z);
//        float e = glm::dot(zaxis, delta);
//        float f = glm::dot(rayDirection, zaxis);
//
//        if ( fabs(f) > 0.001f ){
//
//            float t1 = (e+aabb_min.z)/f;
//            float t2 = (e+aabb_max.z)/f;
//
//            if (t1>t2){float w=t1;t1=t2;t2=w;}
//
//            if ( t2 < tMax )
//                tMax = t2;
//            if ( t1 > tMin )
//                tMin = t1;
//            if (tMin > tMax)
//                return false;
//
//        }else{
//            if(-e+aabb_min.z > 0.0f || -e+aabb_max.z < 0.0f)
//                return false;
//        }
//    }
//    return true;
//}
