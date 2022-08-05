#include "global.h"

// Called by the window when soemthing happens (a message is sent)
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

		// Handle keyboard input...
		case WM_KEYDOWN: 
            switch (wParam) 
            { 
				//
				// Camera Controls
				//
				case VK_LEFT: 
					// Process the LEFT ARROW key. 
					g_eye.x -= 0.2f;
					g_target.x -= 0.2f;
                    break; 
				case VK_RIGHT:
					g_eye.x += 0.2f;
					g_target.x += 0.2f;
					break;
				// Added this, too
				case VK_UP:
					g_eye.y += 0.2f;
					g_target.y += 0.2f;
					break;
				case VK_DOWN:
					g_eye.y -= 0.2f;
					g_target.y -= 0.2f;
					break;
				case VK_PRIOR: case 'p': case 'P':
					// Page up
					g_eye.z += 2.0f;
					//g_target.z += 0.2f;
					break;
				case VK_NEXT: case 'L': case 'l':
					// Page down
					g_eye.z -= 2.0f;
					//g_target.z -= 0.2f;
					break;

				// ******************************************************
				// Controls the 'Primary Object'
				// ******************************************************
				case 'A': case 'a': 
					// Process the LEFT ARROW key. 
					::g_vecObjects[1].Velocity.x -=0.5f;
					//::g_vecObjects[0].PosX += 0.5f;
					//::g_eye.x += 0.5f;
					//::g_target.x += 0.5f;
                    break; 
				case 'D': case 'd':
					::g_vecObjects[1].Velocity.x +=0.5f;
					//::g_vecObjects[0].PosX -= 0.5f;
					//::g_eye.x -= 0.5f;
					//::g_target.x -= 0.5f;
					break;
				// Added this, too
				case 'W': case 'w':
					::g_vecObjects[1].Velocity.z +=0.5f;
					//::g_vecObjects[0].PosZ += 0.5f;
					//::g_eye.z += 0.5f;
					//::g_target.z += 0.5f;
					break;
				case 'S': case 's':
					::g_vecObjects[1].Velocity.z -=0.5f;
					//::g_vecObjects[0].PosZ -= 0.5f;
					//::g_eye.z -= 0.5f;
					//::g_target.z -= 0.5f;
					break;
				case 'z': case 'Z':
					::g_vecObjects[1].Velocity.y +=0.5f;
					//::g_vecObjects[0].PosY += 0.5f;
					//::g_eye.y += 0.5f;
					//::g_target.y += 0.5f;
					break;
				case 'x': case 'X':
					::g_vecObjects[1].Velocity.y -=0.5f;
					//::g_vecObjects[0].PosY -= 0.5f;
					//::g_eye.y -= 0.5f;
					//::g_target.y -= 0.5f;
					break;

				// An stop function to set all velocities to 0
				case 'V': case 'v':
					::g_vecObjects[1].STOP();
					break;

				// ****************************************************
				// Allows the Changing of the Light Type
				// ****************************************************
				case '1':
					::g_theLight.ChangeType(0);
					break;
				case '2':
					::g_theLight.ChangeType(1);
					break;
				case '3':
					::g_theLight.ChangeType(2);
					break;
			}

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}

