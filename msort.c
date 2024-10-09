#include "common.h"

void merge(void *base, size_t elsize, int (*comp)(const void *, const void *), int l, int r) {
    int mid = l + (r - l) / 2;
    // int tmp[mid-l+1];
    void *tmp = malloc(elsize*(mid-l+1));
    // for(int i = l; i <= mid; i++) tmp[i-l] = a[i];
    strncpy(tmp, &base[l], elsize*(mid-l+1));

    int i = 0, j = mid+1, k = l;
    while(i+l<=mid && j<=r) {
        if(comp(&tmp[i], &base[j]) < 0) {
            // a[k++] = tmp[i++];
            strncpy(&base[k], &tmp[i], elsize);
            k += elsize;
            i += elsize;
        }
        else {
            // a[k++] = a[j++];
            strncpy(&base[k], &base[j], elsize);
            k += elsize;
            j += elsize;
        }
    }
    while(i+l<=mid) {
        // a[k++] = tmp[i++];
        strncpy(&base[k], &tmp[i], elsize);
        k += elsize;
        i += elsize;
    }
}

void msort(void *base, size_t elsize, int (*comp)(const void *, const void *), int l, int r) {
    if(l >= r) return;
    int mid = l + (r - l) / 2;
    msort(base, elsize, comp, l, mid);
    msort(base, elsize, comp, mid+1, r);
    merge(base, elsize, comp, l, r);
}

int main() {

    return 0;
}