"use client";

import { useMemo, useState } from "react";

import { motion } from "motion/react";

import { Book, Game, Media, Movie, Series } from "@/lib/api";

import { computeLayout } from "./compute-layout";
import { useGridCols } from "./use-grid-cols";
import { BookContent } from "./child/book-content";
import { GameContent } from "./child/game-content";
import { MovieContent } from "./child/movie-content";
import { SeriesContent } from "./child/series-content";

type Props = {
    medias: Media[];
};

export default function MediaGrid({
    medias,
}: Props) {

    const [expandedId, setExpandedId] =
        useState<string | null>(null);

    const [transitioningIds, setTransitioningIds] =
        useState<Set<string>>(new Set());

    const [isAnimatingLayout, setIsAnimatingLayout] =
        useState(false);

    const gridCols = useGridCols();

    const layouts = useMemo(() => {

        return computeLayout(
            medias,
            expandedId,
            gridCols
        );

    }, [medias, expandedId, gridCols]);

    function handleClick(mediaId: string) {

        if (isAnimatingLayout) {
            return;
        }

        const ids = new Set<string>();

        ids.add(mediaId);

        if (expandedId && expandedId !== mediaId) {
            ids.add(expandedId);
        }

        setTransitioningIds(ids);

        setTimeout(() => {

            setIsAnimatingLayout(true);

            setExpandedId(prev =>
                prev === mediaId
                    ? null
                    : mediaId
            );

        }, 120);
    }

    return (

        <div
            className="
                grid
                auto-rows-[120px]
                gap-4
            "
            style={{
                gridTemplateColumns:
                    `repeat(${gridCols}, minmax(0, 1fr))`
            }}
        >

            {medias.map((media) => {

                const layout =
                    layouts.find(
                        l => l.id === media.id
                    );

                if (!layout) {
                    return null;
                }

                const expanded =
                    expandedId === media.id;

                const isTransitioning = transitioningIds.has(media.id);

                return (

                    <motion.div
                        key={media.id}

                        layout

                        transition={{
                            layout: {
                                duration: 0.45,
                                ease: "easeInOut",
                            }
                        }}

                        onLayoutAnimationComplete={() => {

                            if (!isAnimatingLayout) {
                                return;
                            }

                            setIsAnimatingLayout(false);

                            setTransitioningIds(
                                new Set()
                            );
                        }}

                        style={{
                            gridColumn:
                                `${layout.col} / span ${layout.colSpan}`,

                            gridRow:
                                `${layout.row} / span ${layout.rowSpan}`,
                        }}

                        onClick={() => {
                            handleClick(media.id);
                        }}

                        className="
                            rounded-2xl
                            border
                            bg-card
                            overflow-hidden
                            cursor-pointer
                            shadow-sm
                        "
                    >

                        {/* CONTENU ANIMÉ */}

                        <motion.div
                            animate={{
                                opacity:
                                    isTransitioning
                                        ? 0
                                        : 1,

                                filter:
                                    isTransitioning
                                        ? "blur(6px)"
                                        : "blur(0px)",
                            }}

                            transition={{
                                duration: 0.15,
                            }}

                            className="
                                h-full
                            "
                        >

                            <div className="flex h-full">

                                {/* COVER */}

                                <div
                                    className="
                                        shrink-0
                                        overflow-hidden
                                        aspect-[2/3]
                                        h-full
                                    "
                                >

                                    <img
                                        src={media.coverUrl}
                                        alt={media.title}
                                        className="
                                            w-full
                                            h-full
                                            object-cover
                                        "
                                    />

                                </div>

                                {/* CONTENT */}

                                {media.type === "BOOK" && <BookContent book={media as Book} expanded={expanded} />}
                                {media.type === "MOVIE" && <MovieContent movie={media as Movie} expanded={expanded} />}
                                {media.type === "GAME" && <GameContent game={media as Game} expanded={expanded} />}
                                {media.type === "SERIES" && <SeriesContent series={media as Series} expanded={expanded} />}

                            </div>

                        </motion.div>

                    </motion.div>
                );
            })}

        </div>
    );
}