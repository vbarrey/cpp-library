"use client";

import { useEffect, useState } from "react";

export function useGridCols() {

    const [gridCols, setGridCols] = useState(3);

    useEffect(() => {

        function updateCols() {

            if (window.innerWidth < 768) {

                setGridCols(1);

            } else if (window.innerWidth < 1024) {

                setGridCols(2);

            } else {
                setGridCols(3);
            }
        }

        updateCols();

        window.addEventListener(
            "resize",
            updateCols
        );

        return () => {

            window.removeEventListener(
                "resize",
                updateCols
            );
        };

    }, []);

    return gridCols;
}