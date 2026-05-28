import { Movie } from "@/graphql/generated/graphql";
import { GridItemLayout } from "./layout";

type Cell = {
    occupied: boolean;
};

export function computeLayout(
    medias: Movie[],
    expandedId: string | null,
    gridCols: number,
): GridItemLayout[] {

    const layouts: GridItemLayout[] = [];

    const grid: Cell[][] = [];

    function ensureRow(row: number) {

        while (grid.length < row) {

            grid.push(
                Array.from(
                    { length: gridCols },
                    () => ({
                        occupied: false,
                    })
                )
            );
        }
    }

    function canPlace(
        row: number,
        col: number,
        rowSpan: number,
        colSpan: number,
    ) {

        ensureRow(row + rowSpan);

        for (let r = row; r < row + rowSpan; r++) {

            for (let c = col; c < col + colSpan; c++) {

                if (c > gridCols) {
                    return false;
                }

                if (grid[r - 1][c - 1].occupied) {
                    return false;
                }
            }
        }

        return true;
    }

    function occupy(
        row: number,
        col: number,
        rowSpan: number,
        colSpan: number,
    ) {

        for (let r = row; r < row + rowSpan; r++) {

            for (let c = col; c < col + colSpan; c++) {

                grid[r - 1][c - 1].occupied = true;
            }
        }
    }

    function findPosition(
        rowSpan: number,
        colSpan: number,
    ) {

        let row = 1;

        while (true) {

            ensureRow(row);

            for (let col = 1; col <= gridCols; col++) {

                if (
                    canPlace(
                        row,
                        col,
                        rowSpan,
                        colSpan,
                    )
                ) {

                    return {
                        row,
                        col,
                    };
                }
            }

            row++;
        }
    }

    for (const media of medias) {

        const expanded =
            media.id === expandedId;

        const rowSpan =
            expanded ? Math.min(4, gridCols + 1) : 1;

        const colSpan =
            expanded ? Math.min(3, gridCols) : 1;

        const position =
            findPosition(
                rowSpan,
                colSpan,
            );

        occupy(
            position.row,
            position.col,
            rowSpan,
            colSpan,
        );

        layouts.push({
            id: media.id,

            row: position.row,
            col: position.col,

            rowSpan,
            colSpan,
        });
    }

    return layouts;
}