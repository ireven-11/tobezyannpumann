#include "DebugDraw.h"

//-----------------------------------------------------------------------------
// @brief xz���ʂɌ��_���S�ɃO���b�h����`�悷��
// @param[in] groundSize xz���ʂɕ`�悷��O���b�h���ʂ̑傫��
// @param[in] divideNum  �O���b�h���ʂ𕪊������
//
// @detail ���[���h���_�𒆐S�ɁA�c��groundSize�̑傫����divideNum����������
// ���ꂽ�c���̃O���b�h����`�悷��B
//-----------------------------------------------------------------------------
void DrawGrid(float groundSize, int divideNum)
{
    VECTOR start, end;
    int lineColor = GetColor(128, 50, 50);
    start = end = VGet(0, 0, 0);

    float halfWidth = groundSize * 0.5f;              // �O���b�h���������͈͂̔����̕�
    float addWidth = groundSize / (float)divideNum;   // �O���b�h���������Ԋu

    // �c�������� 
    start.z = -halfWidth;
    end.z = +halfWidth;
    for (int ix = 0; ix < divideNum + 1; ix++)
    {
        start.x = end.x = -halfWidth + ix * addWidth;
        DrawLine3D(start, end, lineColor);
    }

    // ����
    start.x = -halfWidth;
    end.x = +halfWidth;
    for (int iz = 0; iz < divideNum + 1; iz++)
    {
        start.z = end.z = -halfWidth + iz * addWidth;
        DrawLine3D(start, end, lineColor);
    }

    DrawTriangle3D(VGet(-100,0,-100), VGet(-100, 0, 100), VGet(1000, 0, -100), GetColor(100, 50, 50), TRUE);
}