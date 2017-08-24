package com.arpaul.sortndk;

import android.content.Context;
import android.support.v4.view.PagerAdapter;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.Set;

/**
 * Created by ARPaul on 25-08-2017.
 */

class SortPagerAdapter extends PagerAdapter {

    private Context context;
    private LinkedHashMap<String, String> hashSorts;
    private ArrayList<String> arrSortName;

    public SortPagerAdapter(Context context, LinkedHashMap<String, String> hashSorts) {
        this.context = context;
        this.hashSorts = hashSorts;
        getNames();
    }

    public void refresh(LinkedHashMap<String, String> hashSorts) {
        this.hashSorts = hashSorts;
        getNames();
        notifyDataSetChanged();
    }

    void getNames() {
        Set<String> keys = hashSorts.keySet();
        arrSortName = new ArrayList<String>(keys);
    }

    @Override
    public int getCount() {
        if(hashSorts != null)
            return hashSorts.size();
        return 0;
    }

    @Override
    public CharSequence getPageTitle(int position) {
        return arrSortName.get(position);
    }

    @Override
    public int getItemPosition(Object object) {
        return POSITION_NONE;
    }

    @Override
    public Object instantiateItem(ViewGroup container, int position) {
        View view = LayoutInflater.from(context).inflate(R.layout.pager_sort, null);

        TextView tvSortedArray = (TextView) view.findViewById(R.id.tvSortedArray);

        tvSortedArray.setText(hashSorts.get(arrSortName.get(position)));
        container.addView(view);
        return view;
    }

    @Override
    public boolean isViewFromObject(View view, Object object) {
        return view == object;
    }

    @Override
    public void destroyItem(ViewGroup container, int position, Object view) {
        container.removeView((View) view);
    }
}
